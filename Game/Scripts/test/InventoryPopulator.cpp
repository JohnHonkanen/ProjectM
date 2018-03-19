/*
InventoryPopulator class used as a helper to test the warehouse inventories 
at runtime.
Dev: Jack Smith (B00308927)
*/

#include "InventoryPopulator.h"
#include "../PlayerActions.h"
#include "../Resources.h"
#include "core\GameEngine.h"
#include "../ResourceManager.h"
#include "../Resources.h"
#include "../Structure.h"
#include "../Warehouse.h"

InventoryPopulator::InventoryPopulator()
{
}

InventoryPopulator::InventoryPopulator(PlayerActions* pla, Resources* res)
{
	this->pla = pla;
	this->res = res;
}

void InventoryPopulator::Onload()
{
}

void InventoryPopulator::Start()
{
}

/*
	Creates test resources to put into active warehouse inventories
	at runtime on key press. This is detected by the Hud element's
	DrawWidget method which runs at refresh rate and so updates
	quite quickly.
*/
void InventoryPopulator::TestItem(PlayerActions * pla, ResourceManager* resourceManager)
{
	int placeRes1 = GameEngine::manager.inputManager.GetKey("PlaceRes1");
	if (placeRes1 == 1)
	{
		if (!keyHeld)
		{
			keyHeld = true;
		//	dynamic_cast<Warehouse*>(pla->GetSelectedStructure())->GetInventory()
		//		->PlaceItem((resourceManager->FindResource(resourceManager->RandomResources())));// needs random resource
		}
	}
	else {
		keyHeld = false;
	}
}

void InventoryPopulator::Create()
{
}
void InventoryPopulator::Copy(GameObject * gameObject)
{
}
void InventoryPopulator::Update()
{
	
}
void InventoryPopulator::Input()
{

}
