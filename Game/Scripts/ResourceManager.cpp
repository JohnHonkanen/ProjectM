#include "ResourceManager.h"
#include "core\GameEngine.h"
#include "core\InputManager.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

/*Use to add resources into resourcemanagers list*/
Resources ResourceManager::AddResource(int itemID, string itemName, string SKU, int itemPrice, int itemStock, string resourceIcon)
{
	this->resources = Resources(itemID, itemName, SKU, itemPrice, itemStock, resourceIcon);
	this->resourceList[resources.GetItemID()] = resources;
	this->itemIndex = itemID;

	return this->resourceList[itemIndex];
}

/*Use to find resources*/
Resources ResourceManager::FindResource(int itemID)
{
	this->resourceList[itemID] = resources;
	//cout << "Item Name: " << resources.GetName() << " found!" << endl << endl;
	return resources;
}

ResourceManager * ResourceManager::Create(GameObject * gameObject)
{
	ResourceManager *r = new ResourceManager();
	gameObject->AddComponent(r);
	return r;
}

void ResourceManager::Copy(GameObject * copyObject)
{
}

void ResourceManager::Update()
{
	this->resourceList[0] = resources;
	resources.update();

}

void ResourceManager::OnLoad()
{
	GameEngine::manager.inputManager.AddKey("IO", "i", "o");

	Resources resource = AddResource(1, "Milk", "DAIRY", 100, 0, "");
	resource = AddResource(2, "Beef", "MEAT", 200, 0, "");

	FindResource(1);
	FindResource(2);
}
