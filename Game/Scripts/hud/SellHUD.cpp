/*
SellHUD class used to allow the player to sell buildings
Dev: Jack Smith (B00308927)
*/
#include "core\GameObject.h"
#include "core\GameEngine.h"
#include "hud\HUDCanvas.h"
#include "hud\widgets\HUDContainer.h"
#include "hud\widgets\TextWidget.h"
#include "BuildingButton.h"
#include "SellHUD.h"
#include "SellHUDElement.h"
#include "../PlayerActions.h"
#include "../Structure.h"


SellHUD * SellHUD::Create(GameObject * gameObject, EHUD::HUDCanvas *root, PlayerActions* pla, ResourceManager* rManager)
{

	SellHUD *is = new SellHUD();
	is->rManager = rManager;
	is->root = root;
	is->pla = pla;
	gameObject->AddComponent(is);
	return is;
}

EHUD::HUDElement* SellHUD::GetWrapper()
{
	return wrapper;
}

void SellHUD::Copy(GameObject * copyObject)
{
	//Does Nothing.
}

void SellHUD::OnLoad()
{
	//Create our HUD elements based on buildings in Building Manager
	wrapper = EHUD::WHUDContainer::Create(root, { 750, 450, 400, 50 }, "Game/Assets/Textures/Production_HUD_Texture.png", true);
	wrapper->SetActive(false);
	HUD::TextWidget::Create(wrapper, { 12 , 25, 100, 100 }, "Select the building you wish to sell ->", "Game/Assets/Fonts/BlackOpsOne-Regular.ttf", 18, 1, vec3(1, 1, 1));
	SHElement = SellHUDElement::Create(wrapper, { 25, 25, 0, 0 }, pla, rManager);

	Engine::GameEngine::manager.inputManager.AddKey("ToggleSellMenu", "s");
}

void SellHUD::Start()
{
}

void SellHUD::Update()
{
	if (pla->GetSelectedStructure() != nullptr)
	{
		wrapper->SetActive(true);
	}
	else
	{
		wrapper->SetActive(false);
	}
}

void SellHUD::Input()
{

	int openSellMenu = GameEngine::manager.inputManager.GetKey("ToggleSellMenu");

	if (openSellMenu == 1)
	{
		if (!keyHeld)
		{
			keyHeld = true;
			wrapper->SetActive(!wrapper->IsActive());
		}
	}
	else {
		keyHeld = false;
	}
}