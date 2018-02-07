#include "ResourceManager.h"


ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

Resources ResourceManager::AddResource(int itemID, string itemName, string SKU, int itemPrice, int itemStock)
{
	this->resources = Resources(itemID, itemName, SKU, itemPrice, itemStock);
	this->resource[resources.GetItemID()] = resources;
	this->itemIndex = itemID;

	return this->resource[itemIndex];
}


Resources ResourceManager::FindResource(int itemID)
{
	return this->resource[itemID];
}
