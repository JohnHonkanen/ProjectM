/*
Inventory class used as a component of all Stuctures. Gives them the capacity to process and store resources
Dev: Jack Smith (B00308927)
*/


#include "Inventory.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

void Inventory::Copy(GameObject * copyObject)
{

		Inventory * copy = new Inventory();
		copy->INITIAL_STORAGE = Inventory::INITIAL_STORAGE;
		copy->storage = Inventory::storage;
		copy->storageFull = Inventory::storageFull;
		copy->inventoryLevel = Inventory::inventoryLevel;

		copyObject->AddComponent(copy);

}

/*
	Displays the contents of the inventory

	@returns - A string of the Inventory's contents
*/
string Inventory::DisplayInventory()
{
	string contents;

	if (storage.empty())
	{
		contents = "Inventory is empty.";
	}
	else
	{
		for (int i = 0; i < storage.size(); i++)
		{
			contents += "Item: " + storage[i].GetName() + ", Quantity: " + to_string(storage[i].GetItemAmount()) + "\n";
		}
	}
	return contents;
}
string Inventory::GetAtStorageIndex(int index)
{
	string contents;

	if (storage.empty())
	{
		contents = "";
	}
	else
	{
		for (int i = 0; i < storage.size(); i++)
		{
			if (index == i)
			{
				contents += storage[i].GetName() + ", Quantity: " + to_string(storage[i].GetItemAmount());
			}
		}
	}
	return contents;
}
/*
Checks the warehouse storage against the item to see if it has space for the item and whether it can store the item type.

@param - itemType - The type of resource to be sent to the Warehouse

@returns true if the itemType is acceptable to the Warehouse, false if not.
*/
bool Inventory::CheckItem(string itemType)
{
	bool result = false;
	/*
	Checks the item type against a list of acceptable item types.
	*/
	return result;
}
/*
Checks the Inventory to see if the resource type is already contained in the inventory

@param res - The resource to be checked for

@return - true if the resource is present, false if not.
*/
bool Inventory::ContainsItem(Resources res)
{
	bool result = false;
	for (int i = 0; i < storage.size(); i++)
	{
		if (storage[i].GetItemID() == res.GetItemID())
		{
			result = true;
		}
	}
	return result;
}
/*
	Checks the inventory for the resource that is passed in, if it finds it it is placed onto the existing stack
	Any excess resource is sent to the back of the vector. - Does not handle event where all warehouses are full.

	@param res - A resource to be placed in the vector (inside the inventory)
*/
void Inventory::PlaceItem(Resources res)
{
	int storageLimit = (INITIAL_STORAGE * inventoryLevel);
	// If the storage hasn't reached it's limit.
		if (storage.size() < storageLimit)
		{
			if (storage.empty())
			{
				storage.push_back(res);
			}
			else
			{
				storageFull = false;
				for (int i = 0; i < storage.size(); i++)
				{
					if (storage[i].GetItemID() == res.GetItemID())
					{
						if ((storage[i].GetItemAmount() + res.GetItemAmount() > 100))
						{
							res.SetItemAmount((storage[i].GetItemAmount() + res.GetItemAmount()) - 100);
							storage[i].SetItemAmount(100);
							storage.push_back(res);
							atStorageIndex = i;
							break;
						}
						else
						{
							storage[i].SetItemAmount(storage[i].GetItemAmount() + res.GetItemAmount());
						}
					}
					else
					{
						storage.push_back(res);
						atStorageIndex = i;
						break;
					}
				}
			}
		}// If the storage has reached it's limit it must be allowed to fill.
		else if(storage.size() == storageLimit)
		{
			for (int i = 0; i < storage.size(); i++)
			{
				if (storage[i].GetItemID() == res.GetItemID())// if it is the correct item id
				{
					if ((storage[i].GetItemAmount() + res.GetItemAmount() > 100))// if the amount of resource exceeds 100
					{
						int waste = (storage[i].GetItemAmount() + res.GetItemAmount()) - 100;
						storage[i].SetItemAmount(100);
						atStorageIndex = i;
						cout << waste << " Items being wasted.";
						break;
						// if the amount exceeds 100 , set the storage in position i to 100 and print the waste
					}
					else
					{
						storage[i].SetItemAmount(storage[i].GetItemAmount() + res.GetItemAmount());
						// if it does not exceed 100, add it onto the existing entry.
					}
				}
			}
		}
		else
		{
			storageFull = true;
			cout << "Storage is full" << endl;
		}
}

/*
	Removes the entry at the position of the index submitted as a parameter.

	E.g.
	storage.erase(storage.begin() + 5);
	Erases element in slot 5, 

	storage.erase(storage.begin + 0);
	Erases element in the first slot
	etc.
*/
	void Inventory::RemoveAtIndex(int index)
	{
		storage.erase(storage.begin() + (index));
	}
/*
	Does the sending of an item from one building to another
	Takes a res object from the origin building and places it in the destination building.
	Erases the object from the origin building at a given index.
	*/
void Inventory::SendItem(Inventory* originInv, Inventory* destInv, Resources res, int index)
	{
		destInv->PlaceItem(res);
		originInv->RemoveAtIndex(index);
	}
void Inventory::SetResourceQuantity(int newAmount)
{
	r->SetItemAmount(newAmount);
}
int Inventory::GetResourceQuantityAtIndex(int index)
{
	return storage[index].GetItemAmount();
}
void Inventory::SetResourceQuantityAtIndex(int index, int newAmount)
{
	storage[index].SetItemAmount(newAmount);
}


void Inventory::Start()
{
}

void Inventory::Update()
{
}

void Inventory::OnLoad()
{
}
