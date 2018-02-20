/*
InventoryHUD class used at a HUD widget to display the inventories of buildings.
Dev: Jack Smith (B00308927)
*/
#include "InventoryHUD.h"
#include "core\GameObject.h"
#include "core\GameEngine.h"
#include "hud\HUDCanvas.h"
#include "hud\widgets\HUDContainer.h"
#include "hud\widgets\TextWidget.h"
#include "BuildingButton.h"
#include "InventoryHUD.h"
#include "InventoryHUDElement.h"
#include "../PlayerActions.h"
#include "../Warehouse.h"


InventoryHUD * InventoryHUD::Create(GameObject * gameObject, EHUD::HUDCanvas *root, PlayerActions* pla)
{
	
	InventoryHUD *ih = new InventoryHUD();
	ih->root = root;
	ih->pla = pla;
	gameObject->AddComponent(ih);
	return ih;
}

void InventoryHUD::Copy(GameObject * copyObject)
{
	//Does Nothing.
}

void InventoryHUD::OnLoad()
{
	//Create our HUD elements based on buildings in Building Manager
	wrapper = EHUD::WHUDContainer::Create(root, { 120, 500, 400, 200 }, "Game/Assets/Textures/Cblack.jpg", true);
	wrapper->SetActive(false);
	HUD::TextWidget::Create(wrapper, { 10 , 30, 100, 100 }, "Inventory List", "Game/Assets/Fonts/MavenPro-Regular.ttf", 36, 1, vec3(1, 1, 1));
	GameEngine::manager.inputManager.AddKey("OpenInventoryMenu", "e");
	IHElement = InventoryHUDElement::Create(wrapper, { 25, 25, 0, 0 }, inventory, pla);
}

void InventoryHUD::Start()
{
}

void InventoryHUD::Update()
{
	if (pla->GetSelectedStructure() != nullptr && dynamic_cast<Warehouse*>(pla->GetSelectedStructure()) != nullptr)
	{
		wrapper->SetActive(true);
	}
	else
	{
		wrapper->SetActive(false);
	}
}

void InventoryHUD::Input()
{
	int openBuildMenu = GameEngine::manager.inputManager.GetKey("OpenInventoryMenu");

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




