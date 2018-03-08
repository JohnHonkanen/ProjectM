/*
Inventory class used as a component of all Stuctures. Gives them the capacity to process and store resources
Dev: Jack Smith (B00308927)
*/

#include "InventoryV2.h"

Inventory::Inventory()
{
	Inventory(9);
}

Inventory::Inventory(int storageSize)
{
	storage.resize(storageSize);
	storage.reserve(storageSize);

	for (int i = 0; i < storage.size(); i++)
	{
		storage[i] = { nullptr,0 };
	}
}

Inventory::~Inventory()
{
}

bool Inventory::AddItem(Resources *res, int &amount)
{
	int spaceAvailable;
	if (CheckStorageFull(res, spaceAvailable))
	{
		return false;// Can't place any items
	}
	else
	{
		for (int i = 0; i < storage.size(); i++)
		{
			if (amount > 0)
			{
				if (storage[i].resource == nullptr)
				{
					Add(res, i, amount);
				}
				else if (storage[i].resource->GetItemID() == res->GetItemID())
				{
					Add(i, amount);
				}
			}
			else
			{
				return true;
			}
		}
		return (amount == 0);
	}
}

void Inventory::Add(int slot , int &amount)
{
	int amountToAdd;
	int stackLimit = 100;
	if (amount > stackLimit)
	{
		amountToAdd = stackLimit;
	}
	else
	{
		amountToAdd = amount;
	}
	amount -= amountToAdd;

	storage[slot].quantity += amountToAdd;
}

void Inventory::Add(Resources * res, int slot, int & amount)
{
	int amountToAdd;
	int stackLimit = 100;
	if (amount > stackLimit)
	{
		amountToAdd = stackLimit;
	}
	else
	{
		amountToAdd = amount;
	}
	amount -= amountToAdd;

	storage[slot] = { res, amountToAdd };
}

bool Inventory::CheckStorageFull(Resources * res, int & availableSpace)
{
	availableSpace = 0;
	int stackLimit = 100;
	for (Slot slot : storage)
	{
		if (slot.resource == nullptr)
		{
			availableSpace += stackLimit;									
		}
		else if (slot.resource->GetItemID() == res->GetItemID())
		{
			availableSpace += stackLimit - slot.quantity;
		}
	}
	return !(availableSpace > 0);
}

int Inventory::Contains(Resources * res)
{
	int amount = 0;
	for (Slot slot : storage)
	{
		if (slot.resource == nullptr)
		{
			continue;					// If the resource is nullptr go to the next index.
		}
		if (slot.resource->GetItemID() == res->GetItemID())
		{
			amount += slot.quantity;
		}
	}
	return amount;
}

bool Inventory::Remove(Resources * res, int &amount)
{
	for (Slot &slot : storage)
	{
		if (slot.resource == nullptr)
		{
			continue;					// If the resource is nullptr go to the next index.
		}
		if (slot.resource->GetItemID() == res->GetItemID())
		{
			if (amount > 0)
			{
				int temp = amount;
				if (temp > slot.quantity)
				{
					amount -= slot.quantity;
					slot.quantity -= temp;
				}
				else
				{
					slot.quantity -= amount;
					amount = 0;
					return true;
				}
				if (slot.quantity <= 0)
				{
					slot.quantity = 0;
					slot.resource = nullptr;
				}
			}
		}
	}
	return !(amount > 0);
}

bool Inventory::Send(Inventory * dest, Resources * res, int &amount)
{
	if (amount > Contains(res))
	{
		cout << "Not enough in inventory to send that much jeez" << endl;
		return false;
	}
	else
	{
		int availableSpace;
		if (!dest->CheckStorageFull(res, availableSpace))
		{
			int amountToSend;
			if (amount > availableSpace)
			{
				amountToSend = availableSpace;
				amount -= amountToSend;
			}
			else
			{
				amountToSend = amount;
				amount = 0;
			}
			int amountToRemove = amountToSend;
			dest->AddItem(res, amountToSend);
			Remove(res, amountToRemove);
		}
		
	}
	return (amount == 0);
}

void Inventory::Copy(GameObject * copyObject)
{

	Inventory * copy = new Inventory();
	copy->storage = storage;
	copyObject->AddComponent(copy);

}
