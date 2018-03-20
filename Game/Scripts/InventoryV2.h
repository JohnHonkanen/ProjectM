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
#include "ResourceManager.h"


using namespace std;

struct ResourceSlot
{
	ResourceName resource;
	int quantity;
};

namespace v2 {
	class Inventory : public Behaviour
	{
	public:

		enum FILTERMODE { BLACKLIST, WHITELIST };
		struct Slot
		{
			Resources *resource;
			int quantity;
		};

		Inventory();
		Inventory(int storageSize);
		~Inventory();

		// Adds an item to a building
		int AddItem(ResourceName resource, int amount);

		// Used to remove items from buildings
		// Amount is the number of items you wish to remove from a building if you try to remove too many it returns the reminder that couldn't be removed.
		int Remove(ResourceName res, int amount);

		// Used to send items from one building to another
		// Amount is the number of items you wish to send, comes back as the remainder of unsent items.
		int Send(Inventory * dest, ResourceName res, int amount);

		// Checks if the building's storage is full
		// Available space is the space left in the storage for the resource specified. i.e. Depends on stackSize.
		int CheckStorageFull(ResourceName res);

		// Checks if the resources is in a building
		int Contains(ResourceName res);

		vector<ResourceSlot> Contains();

		Slot & At(int index) { return storage[index]; }

		// Returns READ ONLY inventory to be read for HUD for example.
		std::vector<Slot> GetInventory() const { return std::vector<Slot>(storage.begin(),storage.end()); }

		ResourceManager * GetResourceManager() { return rm; }

		void SetResourceManager(ResourceManager * rm);

		void AddFilter(ResourceName resource);

		void SetMode(FILTERMODE mode);

		bool ValidateResource(ResourceName name);

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

		//Deprecated, use method that doesn't require reference to amount.
		bool DAddItem(Resources *res, int &amount);

		// Deprecated, use newer method.
		bool DAddItem(ResourceName resource, int &amount);

		// Deprecated
		bool DRemove(Resources *res, int &amount);

		// Deprecated
		bool DSend(Inventory * dest, Resource * res, int &amount);

		// Deprecated
		bool DCheckStorageFull(Resources * res, int &availableSpace);

		//Deprecated
		int DContains(Resources *res);
		std::vector<ResourceName> filter;

		FILTERMODE mode = BLACKLIST;
		ResourceManager * rm = nullptr;
	};
}

using namespace v2;
#include <cereal/archives/xml.hpp>
//Register Inventory as a derived class
CEREAL_REGISTER_TYPE(v2::Inventory);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Behaviour, v2::Inventory);