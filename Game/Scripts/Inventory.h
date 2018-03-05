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
#include <string>


using namespace std;

class Inventory : public Behaviour
{

private:
	int INITIAL_STORAGE = 9;
	std::vector<Resources> storage;
	bool storageFull = false;
	int inventoryLevel = 1;
	int atStorageIndex;

public:

	Inventory();
	~Inventory();

	void Copy(GameObject *copyObject);

	string DisplayContents();
	void SetInventorySize(int change) { INITIAL_STORAGE * (inventoryLevel+change); }
	std::vector<Resources> GetInventory() { return storage; }
	Resources GetResourceAtIndex(int index) { return storage[index]; }
	bool GetStorageFull() { return storageFull; }
	string GetAtStorageIndex(int index);
	int GetInventoryLevel() { return inventoryLevel; }
	int SetInventoryLevel(int newLevel) { inventoryLevel = newLevel; }
	bool CheckItem(string itemType);
	void PlaceItem(Resources res);
	void RemoveAtIndex(int index);
	bool ContainsItem(Resources res);
	void ChangeResourceQuantity(int change);
	int InventorySize() { return storage.size(); }
	bool InventoryEmpty() { return storage.empty(); }


	void Start();
	void Update();
	void OnLoad();
	template<class Archive>
	void serialize(Archive & ar)
	{
		CEREAL_NVP(storage), CEREAL_NVP(storageFull), CEREAL_NVP(inventoryLevel);
	}
};

#include <cereal/archives/xml.hpp>
//Register Inventory as a derived class
CEREAL_REGISTER_TYPE(Inventory);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Behaviour, Inventory);