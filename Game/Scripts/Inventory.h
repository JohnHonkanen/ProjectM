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
#include "Resources.h"


using namespace std;

class Inventory : public Behaviour
{

private:
	int INITIAL_STORAGE = 9;
	std::vector<Resources> storage;
	bool storageFull = false;
	int inventoryLevel = 1;
	int atStorageIndex;
	Resources * r;
public:

	Inventory();
	~Inventory();

	void Copy(GameObject *copyObject);

	//Returns a string of the entire inventory
	string DisplayInventory();
	//Returns a string of the slot at the index in the inventory
	string GetAtStorageIndex(int index);
	// Returns the entire storage vector
	std::vector<Resources> GetInventory() { return storage; }
	//Returns a resource item at a specific index in the vector
	Resources GetResourceAtIndex(int index) { return storage[index]; }
	//Adjusts the initial storage to the specified number
	void SetInitialStorage(int is) { INITIAL_STORAGE = is; }
	// Sets the inventoryLevel to the specific number
	void SetInventorySize(int change) { INITIAL_STORAGE * (inventoryLevel + change); }
	//Returns the current inventoryLevel
	int GetInventoryLevel() { return inventoryLevel; }
	//Sets the current inventoryLevel to the specified number
	int SetInventoryLevel(int newLevel) { inventoryLevel = newLevel; }
	//Returns whether or not the stroage vector is full
	bool GetStorageFull() { return storageFull; }
	//Returns the .size() property of the vector
	int InventorySize() { return storage.size(); }
	//Returns true is the vector is empty, false  if not
	bool InventoryEmpty() { return storage.empty(); }

	// Does nothing atm
	bool CheckItem(string itemType);
	// Does nothing atm

	//Checks whether the vector contains an item of a specified resource type.
	bool ContainsItem(Resources res);
	// Attempts to add an item to the resource vector
	void PlaceItem(Resources res);
	//Removes a resource at the specified index
	void RemoveAtIndex(int index);
	// Attempts to send an item from one building's inventory to another. - Requires the location of the other
	// Building's inventory and the index of the resource you want to send in the vector.
	void SendItem(Inventory* originInv, Inventory* destInv, Resources res, int index);
	//Sets a resource item's quantity to the specified number
	void SetResourceQuantity(int newAmount);
	//Gets the amount of a resource at the specified index in the vector.
	int GetResourceQuantityAtIndex(int index);
	//Sets a resource already with in the storage vector to a specified amount. Requires the position in the vector
	void SetResourceQuantityAtIndex(int index, int newAmount);

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