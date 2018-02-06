#include "ResourceManager.h"


ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

Resources ResourceManager::AddResource(Resources resource, int itemID)
{
	this->resource[resource.GetItemID()] = resource;
	this->itemIndex = itemID;

	return this->resource[itemIndex];
}


Resources ResourceManager::FindResource(int itemID)
{
	return this->resource[itemID];
}
