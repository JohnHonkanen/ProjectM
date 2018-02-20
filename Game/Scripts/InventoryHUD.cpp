#include "InventoryHUD.h"
#include "core\GameObject.h"
#include "core\GameEngine.h"
#include "hud\HUDCanvas.h"
#include "hud\widgets\HUDContainer.h"
#include "hud\widgets\TextWidget.h"
#include "BuildingButton.h"
#include "InventoryHUD.h"

InventoryHUD * InventoryHUD::Create(GameObject * gameObject, EHUD::HUDCanvas *root)
{
	InventoryHUD *ih = new InventoryHUD();
	ih->root = root;
	gameObject->AddComponent(ih);
	return ih;
}

void InventoryHUD::Copy(GameObject * copyObject)
{
	//Does Nothing.
}

void InventoryHUD::OnLoad()
{
	GameEngine::manager.inputManager.AddKey("OpenBuildMenu", "b");
	//Create our HUD elements based on buildings in Building Manager
	wrapper = EHUD::WHUDContainer::Create(root, { 100 , 100, 400, 380 }, "Game/Assets/Textures/building_hud.jpg", true);
	HUD::TextWidget::Create(wrapper, { 10 , 30, 100, 100 }, "Building List", "Game/Assets/Fonts/MavenPro-Regular.ttf", 36, 1, vec3(1, 1, 1));
	wrapper->SetActive(true);

	HUD::TextWidget::Create(factory, { 230 , 60, 100, 100 }, "Factory", "Game/Assets/Fonts/MavenPro-Regular.ttf", 36, 1, vec3(1, 1, 1));
	BuildingButton *warehouse = BuildingButton::Create(wrapper, { 10 , 260, 380, 100 },
		"Warehouse",
		this,
		"Game/Assets/Textures/building_placeholder_inactive.jpg",
		"Game/Assets/Textures/building_placeholder.jpg",
		"Game/Assets/Textures/building_placeholder_selected.jpg");

	HUD::TextWidget::Create(warehouse, { 160 , 60, 100, 100 }, "Warehouse", "Game/Assets/Fonts/MavenPro-Regular.ttf", 36, 1, vec3(1, 1, 1));
}

void InventoryHUD::Input()
{
	int openBuildMenu = GameEngine::manager.inputManager.GetKey("OpenBuildMenu");

	if (openBuildMenu == 1)
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




