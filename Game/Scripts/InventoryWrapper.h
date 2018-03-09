#pragma once
#include "components\Behaviour.h"
#include "InventoryV2.h"

class InventoryWrapper : public Behaviour
{
private:

public:
	v2::Inventory inventory;
	
	static InventoryWrapper * Create(GameObject* gameObject, ResourceManager* rm, unsigned int inventorySize = 9);
	void Copy(GameObject* gameObject);
};
