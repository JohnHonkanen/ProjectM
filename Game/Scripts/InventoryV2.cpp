/*
Inventory class used as a component of all Stuctures. Gives them the capacity to process and store resources
Dev: Jack Smith (B00308927)
*/

#include "InventoryV2.h"

namespace v2 {
	Inventory::Inventory():Inventory(9)
	{
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



	bool Inventory::DAddItem(Resources *res, int &amount)
	{
		if (!ValidateResource(res->GetResouceID()))
		{
			return false;
		}
		int spaceAvailable;
		if (DCheckStorageFull(res, spaceAvailable))
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

	bool Inventory::DAddItem(ResourceName resource, int &amount)
	{
		if (rm == nullptr)
		{
			cout << "ResourceManager not set. - Use alternative AddItem method or set ResourceManager." << endl;
		}
		return DAddItem(rm->Find(resource), amount);
	}

	int Inventory::Remove(ResourceName res, int amount)
	{
		DRemove(rm->Find(res), amount);
		return amount;
	}

	int Inventory::Send(Inventory * dest, ResourceName res, int amount)
	{
		DSend(dest, rm->Find(res), amount);
		return amount;
	}

	int Inventory::AddItem(ResourceName resource, int amount)
	{
		DAddItem(resource, amount);
		return amount;
	}

	void Inventory::Add(int slot, int &amount)
	{
		int amountToAdd;
		int stackLimit = storage[slot].resource->GetStackLimit();
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
		int stackLimit = res->GetStackLimit();
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

	bool Inventory::DCheckStorageFull(Resources * res, int &availableSpace)
	{
		availableSpace = 0;
		int stackLimit = res->GetStackLimit();
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

	int Inventory::CheckStorageFull(ResourceName res)
	{
		int availableSpace = 0;
		DCheckStorageFull(rm->Find(res), availableSpace);
		return availableSpace;
	}

	int Inventory::DContains(Resources * res)
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

	int Inventory::Contains(ResourceName res)
	{
		return DContains(rm->Find(res));
	}

	bool Inventory::DRemove(Resources * res, int &amount)
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

	bool Inventory::DSend(Inventory * dest, Resource * res, int &amount)
	{
		if (amount > DContains(res))
		{
			cout << "Not enough inventory slot" << endl;
			return false;
		}
		else
		{
			int availableSpace;
			if (!dest->DCheckStorageFull(res, availableSpace))
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
				dest->DAddItem(res, amountToSend);
				DRemove(res, amountToRemove);
			}

		}
		return (amount == 0);
	}

	void Inventory::SetResourceManager(ResourceManager * rm)
	{
		this->rm = rm;
	}

	void Inventory::AddFilter(ResourceName resource)
	{
		filter.push_back(resource);
	}

	void Inventory::SetMode(FILTERMODE mode)
	{
		this->mode = mode;
	}

	bool Inventory::ValidateResource(ResourceName name)
	{
		if (filter.empty())
		{
			return true;
		}

		for (auto f : filter)
		{
			if (f == name)
			{
				switch (mode)
				{
				case Inventory::BLACKLIST:
					return false;
					break;
				case Inventory::WHITELIST:
					return true;
					break;
				default:
					break;
				}
			}
		}
		switch (mode)
		{
		case v2::Inventory::BLACKLIST:
			return true;
			break;
		case v2::Inventory::WHITELIST:
			return false;
			break;
		default:
			break;
		}
	}

	void Inventory::Copy(GameObject * copyObject)
	{

		Inventory * copy = new Inventory();
		copy->storage = storage;
		copyObject->AddComponent(copy);

	}
}