#include "ResourceManager.h"


ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

/*Use to add resources into resourcemanagers list*/
Resources ResourceManager::AddResource(int itemID, string itemName, string SKU, int itemPrice, int itemStock)
{
	this->resources = Resources(itemID, itemName, SKU, itemPrice, itemStock);
	this->resourceList[resources.GetItemID()] = resources;
	this->itemIndex = itemID;

	return this->resourceList[itemIndex];
}

/*Use to find resources*/
Resources ResourceManager::FindResource(int itemID)
{
	return this->resourceList[itemID];
}
