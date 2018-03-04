#include "PlayerEconHUD.h"
#include "core\GameObject.h"
#include "hud\HUDCanvas.h"
#include "hud\widgets\HUDContainer.h"
#include "hud\widgets\TextWidget.h"
#include "PlayerEconHUDElement.h"


PlayerEconHUD * PlayerEconHUD::Create(GameObject * gameObject, EHUD::HUDCanvas * root, PlayerEconManager * playerEconManager)
{
	PlayerEconHUD* playerEconHUD = new PlayerEconHUD();
	playerEconHUD->playerEconManager = playerEconManager;
	playerEconHUD->root = root;

	return playerEconHUD;
}

void PlayerEconHUD::Copy(GameObject * gameObject)
{
	// Does nothing
}

void PlayerEconHUD::OnLoad()
{
	// Create HUD element for player economy
	wrapper = EHUD::WHUDContainer::Create(root, {300, 300, 300, 300}, "Game/Assets/Textures/pink.jpg", true);
	wrapper->SetActive(true);

	Engine::GameEngine::manager.inputManager.AddKey("togglePlayerEcon", "u");
}

void PlayerEconHUD::Start()
{

}

void PlayerEconHUD::Update()
{

}

void PlayerEconHUD::Input()
{
	int userInput = Engine::GameEngine::manager.inputManager.GetKey("togglePlayerEcon");

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
