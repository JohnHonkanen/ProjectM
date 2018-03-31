#include "MarketHUD.h"
#include "core\GameObject.h"
#include "hud\HUDCanvas.h"
#include "hud/widgets/HUDContainer.h"
#include "../MarketManager.h"
#include "hud\widgets\TextWidget.h"
#include "MarketHudElement.h"
#include "FunctionPtrButton.h"

class MarketHubPurchaseBinder : public FunctionPtrBinder
{
public:
	MarketHubPurchaseBinder(MarketHUD *marketHud, LocalMarket* market, int buttonID) : marketHud(marketHud), market(market) { this->buttonID = buttonID; };
	void Call() {
		auto marketList = market->GetResources();
		itemID = this->buttonID;

		//if resource purchased...
		switch (itemID) {
		case 0:
			market->IncreaseBasePriceOf(itemID, 5);
			market->DecreaseItemStock(itemID, 100);
			cout << "New BasePrice of Item: " + to_string(market->GetBasePriceOf(this->buttonID)) << endl;
			break;
		case 1:
			market->IncreaseBasePriceOf(itemID, 5);
			market->DecreaseItemStock(itemID, 100);
			break;
		case 2:
			market->IncreaseBasePriceOf(itemID, 5);
			market->DecreaseItemStock(itemID, 100);
			break;
		case 3:
			market->IncreaseBasePriceOf(itemID, 5);
			market->DecreaseItemStock(itemID, 100);
			break;
		case 4:
			market->IncreaseBasePriceOf(itemID, 5);
			market->DecreaseItemStock(itemID, 100);
			break;
		case 5:
			market->IncreaseBasePriceOf(itemID, 5);
			market->DecreaseItemStock(itemID, 100);
			break;
		case 6:
			market->IncreaseBasePriceOf(itemID, 5);
			market->DecreaseItemStock(itemID, 100);
			break;
		default:
			cout << "Default case called: " << this->buttonID << " SELL: " + market->GetNameOfMarket() << endl;
			break;
		}
	}
private:
	MarketHUD * marketHud;
	LocalMarket *market;
	int buttonID, itemID;
};

class MarketHubSaleBinder : public FunctionPtrBinder
{
public:
	MarketHubSaleBinder(MarketHUD *marketHud, LocalMarket* market, int buttonID) : marketHud(marketHud), market(market) { this->buttonID = buttonID; };
	void Call() {
		auto marketList = market->GetResources();
		itemID = this->buttonID;

		// If resource sold...
		switch (itemID) {
		case 0:
			market->DecreaseBasePriceOf(itemID, 5);
			market->IncreaseItemStock(itemID, 100);
			cout << "New BasePrice of Item: " + to_string(market->GetBasePriceOf(this->buttonID)) << endl;
			break;
		case 1:
			market->DecreaseBasePriceOf(itemID, 5);
			market->IncreaseItemStock(itemID, 100);
			break;
		case 2:
			market->DecreaseBasePriceOf(itemID, 5);
			market->IncreaseItemStock(itemID, 100);
			break;
		case 3:
			market->DecreaseBasePriceOf(itemID, 5);
			market->IncreaseItemStock(itemID, 100);
			break;
		case 4:
			market->DecreaseBasePriceOf(itemID, 5);
			market->IncreaseItemStock(itemID, 100);
			break;
		case 5:
			market->DecreaseBasePriceOf(itemID, 5);
			market->IncreaseItemStock(itemID, 100);
			break;
		case 6:
			market->DecreaseBasePriceOf(itemID, 5);
			market->IncreaseItemStock(itemID, 100);
			break;
		default:
			cout << "Default case called: " << this->buttonID << " BUY: " + market->GetNameOfMarket() << endl;
			break;
		}

		cout << "SELL: " + market->GetNameOfMarket() << endl;


	}
private:
	MarketHUD * marketHud;
	LocalMarket *market;
	int buttonID, itemID;
};

MarketHUD * MarketHUD::Create(GameObject * gameObject, EHUD::HUDCanvas * root, MarketManager * marketManager)
{
	MarketHUD *marketHUD = new MarketHUD();
	marketHUD->marketManager = marketManager;
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

	auto marketList1 = market1->GetResources();
	auto marketList2 = market2->GetResources();
	int y = 0;
	float market2XOffset = 1112;
	float increment = 45;
	int buttonID = 0;

	for (auto resource : marketList1) {
		buttonID = y;
		// Local Market Buttons (Market1)
		buyButton = FunctionPtrButton::Create(wrapper, { 75, 105 + y * increment, 16, 16 }, "Game/Assets/Textures/Market/plus.png", new MarketHubPurchaseBinder(this, market1, buttonID));
		sellButton = FunctionPtrButton::Create(wrapper, { 150, 105 + y * increment, 16, 16 }, "Game/Assets/Textures/Market/minus.png", new MarketHubSaleBinder(this, market1, buttonID));

		// Galactic Market Buttons (Market2)
		buyButton = FunctionPtrButton::Create(wrapper, { market2XOffset, 105 + y * increment, 16, 16 }, "Game/Assets/Textures/Market/plus.png", new MarketHubPurchaseBinder(this, market2, buttonID));
		sellButton = FunctionPtrButton::Create(wrapper, { market2XOffset + 75, 105 + y * increment, 16, 16 }, "Game/Assets/Textures/Market/minus.png", new MarketHubSaleBinder(this, market2, buttonID));
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
