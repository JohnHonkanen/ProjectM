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
	this->resourceList[resources.GetItemID()] = resources;
	this->itemIndex = itemID;

	return this->resourceList[itemIndex];
}


Resources ResourceManager::FindResource(int itemID)
{
	return this->resourceList[itemID];
}
