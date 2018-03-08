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
public:
	struct Slot
	{
		Resources *resource;
		int quantity;
	};

	Inventory();
	Inventory(int storageSize);
	~Inventory();

	// Adds an item to a building
	// Amount is the amount you want to add to a building but if you try to add to many items it is returned as the remainder.
	bool AddItem(Resources *res, int &amount);

	// Checks if the building's storage is full
	// Available space is the space left in the storage for the resource specified. i.e. Depends on stackSize.
	bool CheckStorageFull(Resources *res, int &availableSpace);

	// Checks if the resources is in a building
	int Contains(Resources *res);

	// Used to remove items from buildings
	// Amount is the number of items you wish to remove from a building if you try to remove too many it returns the reminder that couldn't be removed.
	bool Remove(Resources *res, int &amount);

	// Used to send items from one building to another
	// Amount is the number of items you wish to send, comes back as the remainder of unsent items.
	bool Send(Inventory * dest , Resources * res, int &amount);

	// Returns READ ONLY inventory to be read for HUD for example.
	const std::vector<Slot const*> &GetInventory() const { return std::vector <Slot const*>(storage.begin(),storage.end()); }

	void Copy(GameObject *copyObject);

	template<class Archive>
	void serialize(Archive & ar)
	{
		CEREAL_NVP(storage);
	}

private:
	std::vector<Slot> storage;
	void Add(Resources *res, int slot, int &amount);
	void Add(int slot, int &amount);
};

#include <cereal/archives/xml.hpp>
//Register Inventory as a derived class
CEREAL_REGISTER_TYPE(Inventory);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Behaviour, Inventory);