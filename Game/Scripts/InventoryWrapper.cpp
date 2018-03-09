#include "InventoryWrapper.h"

InventoryWrapper * InventoryWrapper::Create(GameObject* gameObject, unsigned int inventorySize)
{
	InventoryWrapper * iw = new InventoryWrapper();
	iw->inventory = Inventory(inventorySize);
	gameObject->AddComponent(iw);

	return iw;
}

void InventoryWrapper::Copy(GameObject * gameObject)
{
	/*Create(gameObject, inventory.GetInventory().size());*/
}
