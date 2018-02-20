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
	
	this->itemIndex = itemID;

	this->resourceList[itemIndex] = this->resources;

	return this->resourceList[itemIndex];
}

/*Use to find resources*/
Resources ResourceManager::FindResource(int itemID)
{
	
	cout << "Item Name: " << this->resourceList[itemID].GetName() << " found!" << endl << endl;
	return this->resourceList[itemID];;
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

	Resources resource = AddResource(1, "Milk", "DAIRY", 1, 0, "Game/Assets/Textures/milk-16.png");
	resource = AddResource(2, "Beef", "MEAT", 2, 0, "Game/Assets/Textures/steak-16.png");


	//FindResource(0);
}

int ResourceManager::NumberOfActiveResources()
{
	int count = 0;
	for (int i = 1; i <= 7; i++) {
		
		cout << "Resource Number: " + count << endl;
		return count++;
	}
}
