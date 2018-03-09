#include "InventoryWrapper.h"

InventoryWrapper * InventoryWrapper::Create(GameObject* gameObject, ResourceManager* rm, unsigned int inventorySize)
{
	InventoryWrapper * iw = new InventoryWrapper();
	iw->inventory = Inventory(inventorySize);
	iw->inventory.SetResourceManager(rm);
	gameObject->AddComponent(iw);

	return iw;
}

void InventoryWrapper::Copy(GameObject * gameObject)
{
	Create(gameObject, inventory.GetResourceManager(), inventory.GetInventory().size());
}
