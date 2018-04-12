/*
InventoryPopulator class used as a helper to test the warehouse inventories
at runtime.
*/

#pragma once
#include "components\Behaviour.h"

class InventoryPopulator : public Behaviour
{
public:
	InventoryPopulator();

	InventoryPopulator(class PlayerActions* pla, class Resources* res);
	void Onload();
	// Creates test items at runtime for warehouse inventories
	void Start();
	void TestItem(PlayerActions * pla, class ResourceManager* resourceManager);
	void Create();
	void Copy(GameObject* gameObject);
	void Update();
	void Input();

private:
	// Varibles declared and forward declared.
	bool keyHeld = false;
	class PlayerActions* pla;
	class Resources* res;
	class ResourceManager* resourceManager;
};
