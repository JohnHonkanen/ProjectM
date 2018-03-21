#include "MarketHUD.h"
#include "core\GameObject.h"
#include "hud\HUDCanvas.h"
#include "hud/widgets/HUDContainer.h"
#include "../MarketManager.h"
#include "hud\widgets\TextWidget.h"
#include "MarketHudElement.h"

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
