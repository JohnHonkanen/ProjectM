#include "MarketHUD.h"
#include "core\GameObject.h"
#include "hud\HUDCanvas.h"
#include "hud/widgets/HUDContainer.h"
#include "../MarketManager.h"
#include "hud\widgets\TextWidget.h"
#include "MarketHudElement.h"
#include "FunctionPtrButton.h"
#include "../PlayerEconManager.h"
#include "../GameManager.h"
#include "../Dock.h"

class MarketHubPurchaseBinder : public FunctionPtrBinder
{
public:
	MarketHubPurchaseBinder(MarketHUD *marketHud, LocalMarket* market, int buttonID, PlayerEconomy* pEcon) : marketHud(marketHud), market(market), pEcon(pEcon)
	{ this->buttonID = buttonID; };
	void Call() {
		auto marketList = market->GetResources();
		auto pEconList = pEcon->GetPlayerEconList();
		Dock* dock = static_cast<Dock*>(GameManager::gameManager->GetHub()->FindNearest(StructureType::DOCK, 0, 0));
		itemID = this->buttonID;
		
		//if resource purchased...
		if (market->GetItemStock(itemID) <= 100) {
			cout << "Insufficient amount of: " + market->GetNameOfItem(itemID) + " in " + market->GetNameOfMarket() + " storage!" << endl;
		}
		else {
			if (dock != nullptr) {
				// Check if enough funds available in pEcon to complete purchase
				if (pEcon->GetGBAmount() > market->GetBasePriceOf(itemID)) {
					// Remove gold bars from HUB Inventory + request drone to send
					pEcon->RemoveGoldBars(market->GetBasePriceOf(itemID));

					dock->AddToMarketDump(market->GetResourceName(itemID), 100);
					// if item received at dock...
					// Adjust price/demand/stock amount of item
					market->IncreaseBasePriceOf(itemID, 10);
					market->DecreaseItemStock(itemID, 100);
					market->IncreaseDemandOf(itemID, 5);

					// Request drone to pick up item : WIP
				}
			}
			
			if (dock == nullptr) {
				cout << "::ERROR::DOCK_IS_NULL_PTR::" << endl;
			}

			// If NOT enough funds available in pEcon to complete purchase
			if (pEcon->GetGBAmount() < market->GetBasePriceOf(itemID)) {
				cout << "Insufficient funds in pEcon detected!" << endl;
			}
		}
	}

private:
	MarketHUD * marketHud;
	LocalMarket *market;
	PlayerEconManager *pEconManager;
	PlayerEconomy* pEcon;
	int buttonID, itemID;
};

class MarketHubSaleBinder : public FunctionPtrBinder
{
public:
	MarketHubSaleBinder(MarketHUD *marketHud, LocalMarket* market, int buttonID, PlayerEconomy* pEcon) : marketHud(marketHud), market(market), pEcon(pEcon){ this->buttonID = buttonID; };
	void Call() {
		auto marketList = market->GetResources();
		auto pEconList = pEcon->GetPlayerEconList();
		Dock* dock = static_cast<Dock*>(GameManager::gameManager->GetHub()->FindNearest(StructureType::DOCK, 0, 0));
		itemID = this->buttonID;

		// If resource sold...

		if (market->GetItemStock(itemID) >= market->GetMaxLimit()) {
			cout << "Insufficient space for: " + market->GetNameOfItem(itemID) + " in " + market->GetNameOfMarket() + " storage!" << endl;
		}
		else {
			if (dock != nullptr) {
				// request drone to send item to dock
				dock->AddToMarketRequest(market->GetResourceName(itemID), 100);
			}
			
		}
	}
private:
	MarketHUD * marketHud;
	LocalMarket *market;
	PlayerEconManager *pEconManager;
	PlayerEconomy* pEcon;
	int buttonID, itemID;
};

MarketHUD * MarketHUD::Create(GameObject * gameObject, EHUD::HUDCanvas * root, MarketManager * marketManager)
{
	MarketHUD *marketHUD = new MarketHUD();
	marketHUD->marketManager = marketManager;
	marketHUD->pEconManager = &GameManager::gameManager->playerEconManager;
	marketHUD->root = root;

	gameObject->AddComponent(marketHUD);

	return marketHUD;
}

EHUD::HUDElement * MarketHUD::GetWrapper()
{
	return wrapper;
}

void MarketHUD::Copy(GameObject * copyObject)
{
	// Does nothing
}

void MarketHUD::OnLoad()
{

	int increment = 50;
	// Create HUD elements based on markets in marketManager
	wrapper = EHUD::WHUDContainer::Create(root,{0, 0, 0, 0}, "Game/Assets/Textures/transparent_black.png", true);
	wrapper2 = EHUD::WHUDContainer::Create(wrapper, { 0, 0, 240, 1000 }, "Game/Assets/Textures/transparent_black.png", true);
	wrapper3 = EHUD::WHUDContainer::Create(wrapper, { 1040, 0, 240, 1000 }, "Game/Assets/Textures/transparent_black.png", true);

	

	WidgetToggleButton::Create(root, { 147 , 647 , 60,60 }, "Game/Assets/Textures/galactic.png", wrapper);

	wrapper->SetActive(false);

	Engine::GameEngine::manager.inputManager.AddKey("ToggleMarketHUD", "m");
}

void MarketHUD::Start()
{
	market1 = marketManager->FindPersistentMarket(MarketName::Local);
	market2 = marketManager->FindPersistentMarket(MarketName::Galactic);
	pEcon = pEconManager->FindPlayerEcon(EconName::Player_Econ);

	auto marketList1 = market1->GetResources();
	auto marketList2 = market2->GetResources();
	int y = 0;
	float market2XOffset = 1112;
	float increment = 45;
	int buttonID = 0;

	for (auto resource : marketList1) {
		buttonID = y;
		// Local Market Buttons (Market1)
		buyButton = FunctionPtrButton::Create(wrapper, { 75, 105 + y * increment, 16, 16 }, "Game/Assets/Textures/Market/plus.png", new MarketHubPurchaseBinder(this, market1, buttonID, pEcon));
		sellButton = FunctionPtrButton::Create(wrapper, { 150, 105 + y * increment, 16, 16 }, "Game/Assets/Textures/Market/minus.png", new MarketHubSaleBinder(this, market1, buttonID, pEcon));

		// Galactic Market Buttons (Market2)
		buyButton = FunctionPtrButton::Create(wrapper, { market2XOffset, 105 + y * increment, 16, 16 }, "Game/Assets/Textures/Market/plus.png", new MarketHubPurchaseBinder(this, market2, buttonID, pEcon));
		sellButton = FunctionPtrButton::Create(wrapper, { market2XOffset + 75, 105 + y * increment, 16, 16 }, "Game/Assets/Textures/Market/minus.png", new MarketHubSaleBinder(this, market2, buttonID, pEcon));
		y++;
	}

	MHElement = MarketHUDElement::Create(wrapper2, { 25, 25, 0, 0 }, market1);

	/*Temp Disabled*/
	MHElement2 = MarketHUDElement::Create(wrapper3, { 25, 25, 0, 0 }, market2);
}

void MarketHUD::Update()
{
}

void MarketHUD::Input()
{
	int userInput = Engine::GameEngine::manager.inputManager.GetKey("ToggleMarketHUD");

	if (userInput == 1) {
		if (keyReleased == true) {
			keyReleased = false;

			wrapper->SetActive(!wrapper->IsActive());

		}
	}
	else {
		if (userInput == 0) {
			keyReleased = true;
		}
	}

}
