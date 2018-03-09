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

	bool Inventory::AddItem(Resources *res, int &amount)
	{
		if (!ValidateResource(res->GetResouceID()))
		{
			return false;
		}
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

	bool Inventory::AddItem(ResourceName resource, int & amount)
	{
		if (rm == nullptr)
		{
			cout << "ResourceManager not set. - Use alternative AddItem method or set ResourceManager." << endl;
		}
		return AddItem(rm->Find(resource), amount);
	}

	void Inventory::Add(int slot, int &amount)
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