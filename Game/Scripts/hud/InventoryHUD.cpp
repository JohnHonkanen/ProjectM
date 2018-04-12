 /*
InventoryHUD class used at a HUD widget to display the inventories of buildings.
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


InventoryHUD * InventoryHUD::Create(GameObject * gameObject, EHUD::HUDCanvas *root, PlayerActions* pla, ResourceManager* rManager)
{
	
	InventoryHUD *ih = new InventoryHUD();
	ih->rManager = rManager;
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
	wrapper = EHUD::WHUDContainer::Create(root, { 600, 100, 210, 195 }, "Game/Assets/Textures/Production_HUD_Texture.png", true);
	wrapper->SetActive(false);
	HUD::TextWidget::Create(wrapper, { 12.5 , 20, 100, 100 }, "Inventory", "Game/Assets/Fonts/BlackOpsOne-Regular.ttf", 18, 1, vec3(1, 1, 1));
	GameEngine::manager.inputManager.AddKey("OpenInventoryMenu", "e");
	IHElement = InventoryHUDElement::Create(wrapper, { 25, 25, 0, 0 }, pla, rManager);
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




