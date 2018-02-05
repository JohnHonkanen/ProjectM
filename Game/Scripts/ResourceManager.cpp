#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
	this->Init();
}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::Init()
{
	Resources resource1 = Resources(1, "testItem", "TEST", 100, 0);
	this->AddResource(resource1);

}

void ResourceManager::AddResource(Resources resource)
{
	this->resource[resource.GetItemID()] = resource;
	this->itemIndex++;

}

Resources ResourceManager::FindResource(int itemID)
{
	return this->resource[itemID];
}
