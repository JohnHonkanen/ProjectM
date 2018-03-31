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

		/* WIP: Add code to:
		1) Check if storage space is available + player has enough gold.
		2) if yes, request resource purchased to be transported to warehouse from marketplace by a drone.

		Waiting on above methods to be developed...
		*/

		//if resource purchased...
		if (market->GetItemStock(itemID) <= 0) {
			cout << "Insufficient amount of: " + market->GetNameOfItem(itemID) + " in " + market->GetNameOfMarket() + " storage!" << endl;
		}
		else {
			market->IncreaseBasePriceOf(itemID, 5);
			market->DecreaseItemStock(itemID, 100);
			cout << "New BasePrice of Item: " + to_string(market->GetBasePriceOf(this->buttonID)) << endl;
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

		/* WIP: Add code to:
		1) Check if item and amount is available via the hub.
		2) if yes, request resource purchased to be transported to market by a drone.

		Waiting on above methods to be developed...
		*/


		// If resource sold...

		if (market->GetItemStock(itemID) >= 9900) {
			cout << "Insufficient space for: " + market->GetNameOfItem(itemID) + " in " + market->GetNameOfMarket() + " storage!" << endl;
		}
		else {
			market->DecreaseBasePriceOf(itemID, 5);
			market->IncreaseItemStock(itemID, 100);
			cout << "New BasePrice of Item: " + to_string(market->GetBasePriceOf(this->buttonID)) << endl;
		}
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
