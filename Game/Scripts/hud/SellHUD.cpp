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
#include "../PlayerEconomy.h"
#include "../GameManager.h"
#include  "../task_system/Task.h"
#include "../task_system/drones/DroneController.h"
#include "../Dock.h"
#include "../Warehouse.h"
//#include "../UnbuildableZone.h"


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
	wrapper = EHUD::WHUDContainer::Create(root, { 750, 450, 400, 100 }, "Game/Assets/Textures/Production_HUD_Texture.png", true);
	wrapper->SetActive(false);
	HUD::TextWidget::Create(wrapper, { 20 , 25, 100, 100 }, "Select the building you wish to sell", "Game/Assets/Fonts/BlackOpsOne-Regular.ttf", 18, 1, vec3(1, 1, 1));
	HUD::TextWidget::Create(wrapper, { 20 , 75, 100, 100 }, "Once selected, press L to confirm", "Game/Assets/Fonts/BlackOpsOne-Regular.ttf", 18, 1, vec3(1, 1, 1));
	SHElement = SellHUDElement::Create(wrapper, { 25, 25, 0, 0 }, pla, rManager);

	Engine::GameEngine::manager.inputManager.AddKey("ToggleSellMenu", "l");

}

void SellHUD::Start()
{
}

void SellHUD::Update()
{
}

// Handles Input from the player
void SellHUD::Input()
{

    openSellMenu = GameEngine::manager.inputManager.GetKey("ToggleSellMenu");

	if (openSellMenu == 1)
	{
		if (pla->GetSelectedStructure() != nullptr 
			&& dynamic_cast<Hub*>(pla->GetSelectedStructure()) == nullptr
			/*&& dynamic_cast<UnbuildableZone*>(pla->GetSelectedStructure()) == nullptr*/)
		{
			
			// If the structure is a dock with a ship docked send the ship away
			if(dynamic_cast<Dock*>(pla->GetSelectedStructure()) != nullptr)
			{
				auto temp = pla->GetSelectedStructure();
				Dock* d = dynamic_cast<Dock*>(temp);
				d->SetDockDestoryed(true);
			}
			// Clear a warehouse inventory when it's deleted.
			if(dynamic_cast<Warehouse*>(pla->GetSelectedStructure()) != nullptr)
			{
				pla->GetSelectedStructure()->GetInventory().RemoveAll();
			}
			// Complete the task the drones currently have that are connected to the building
			vector<v1::TaskSystem::DroneController*> droneController = pla->GetSelectedStructure()->GetRegisteredDrones();
			for(int i = 0; i < droneController.size(); i++)
			{
				droneController.at(i)->CancelTasks(droneController.at(i));
			}
			
			wrapper->SetActive(true);
			// Add some money to the player's Hub.
			GameManager::gameManager->playerEconManager.FindPlayerEcon(EconName::Player_Econ)->AddGoldBars(50*(pla->GetSelectedStructure()->GetProductionEfficiency()));
			GameManager::gameManager->buildingManager.GetBuilding(pla->GetSelectedStructure()->GetName());
			std::cout << "Sold building for 50 gold" << std::endl;
			// Remove the building from the system.
			float tileWidth = float(pla->GetSelectedStructure()->GetTileWidth());
			int xCoord, yCoord;
			pla->GetSelectedStructure()->GetTilePosition(xCoord, yCoord);
			GameManager::gameManager->GetHub()->RemoveBuildingFromLists(pla->GetSelectedStructure(),xCoord,yCoord, tileWidth, pla->GetSelectedStructure()->gameObject->name);
			// Destroy the building 
			pla->GetSelectedStructure()->gameObject->Destroy();
			pla->GetSelectedStructure()->gameObject = nullptr;
			// Deselect building
			pla->SetSelectedStructureNull();
			
		}
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