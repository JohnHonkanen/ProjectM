/*
Inventory class used as a component of all Stuctures. Gives them the capacity to process and store resources
Dev: Jack Smith (B00308927)
*/

#pragma once
#include "components\Behaviour.h"
#include "Resources.h"
#include "core/GameObject.h"
#include <cereal\cereal.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <vector>

using namespace std;

class Inventory : public Behaviour
{

private:

	std::vector<Resources> storage;
	Resources *res;
	const int INITIAL_STORAGE = 9;
	bool storageFull = false;
	int itemsStored = 0;
	int inventoryLevel = 1;

public:

	Inventory();
	~Inventory();

	string DisplayContents();
	void SetInventorySize(int change) { INITIAL_STORAGE * (inventoryLevel+change); }
	int GetItemsStored() { return itemsStored; }
	std::vector<Resources> GetInventory() { return storage; }
	bool CheckItem(string itemType);
	void PlaceItem(Resources res);
	bool ContainsItem(Resources res);
	void ChangeResourceQuantity(int change);
	int InventorySize() { return storage.size(); }

	void Start();
	void Update();
	void OnLoad();
	template<class Archive>
	void serialize(Archive & ar)
	{
		CEREAL_NVP(storage), CEREAL_NVP(storageFull), CEREAL_NVP(itemsStored), CEREAL_NVP(inventoryLevel);
	}
};

using namespace Engine;

#include <cereal/archives/xml.hpp>
//Register Inventory as a derived class
CEREAL_REGISTER_TYPE(Inventory);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Behaviour, Inventory);