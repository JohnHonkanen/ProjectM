/*
Inventory class used as a component of all Stuctures. Gives them the capacity to process and store resources
Dev: Jack Smith (B000308927)
*/


#include "Inventory.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
	delete[] res;
}

/*
	Displays the contents of the inventory

	@returns - A string of the Inventory's contents
*/
string Inventory::DisplayContents()
{
	string contents;

	for (int i = 0; i < storage.size(); i++)
	{
		contents += "Item name : " + storage[i].GetName() + "Item Quantity : " + storage[i].GetItemAmount() + "\n";
	}

	return contents;
}

/*
	Checks the inventory for the resource that is passed in, if it finds it it is placed onto the existing stack
	Any excess resource is sent to the back of the vector. - Does not handle event where all warehouses are full.

	@param res - A resource to be placed in the vector (inside the inventory)

	@returns - true if a succesful placement is made, false if not.
*/
void Inventory::PlaceItem(Resources res)
{
	for (int i = 0; i < storage.size; i++)
	{
		if (storage.size < (INITIAL_STORAGE * inventoryLevel))
		{
			if (storage[i].GetItemID() == res.GetItemID())
			{
				if ((storage[i].GetItemAmount() + res.GetItemAmount() > 100))
				{
					storage[i].SetItemAmount(100);
					res.SetItemAmount((storage[i].GetItemAmount() + res.GetItemAmount()) - 100);
					storage.push_back(res);
				}
				else
				{
					storage[i].SetItemAmount(storage[i].GetItemAmoumt() + res.GetItemAmount());
				}
			}
			else
			{
				storage.push_back(res);
			}	
		}
	}
}
// Will need to call this method on all the individual warehouses, another method can traverse through the warehouses 
// Call this method as it does so.

/*
	Checks the Inventory to see if the resource type is already contained in the inventory

	@param res - The resource to be checked for

	@return - true if the resource is present, false if not.
*/
bool Inventory::ContainsItem(Resources res)
{
	bool result = false;
	for (int i = 0; i < storage.size; i++)
	{
		if (storage[i].GetItemID() == res.GetItemID())
		{
			result = true;
		}
	}
	return result;
}
void Inventory::ChangeResourceQuantity(int change)
{
	res->SetItemAmount(-change);
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

void Inventory::Start()
{
}

void Inventory::Update()
{
}

void Inventory::OnLoad()
{
}
