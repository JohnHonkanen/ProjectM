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
Resources ResourceManager::AddResource(ResourceName resName, string itemName, string SKU, int itemPrice, int itemStock, string resourceIcon, 
	int stackLimit, int demand, int productionRate, int productionTimer)
{
	this->resources = Resources(resName, itemName, SKU, itemPrice, itemStock, resourceIcon, stackLimit, demand, productionRate, productionTimer);
	
	this->itemIndex = static_cast<int>(resName);

	this->resourceList[itemIndex] = this->resources;

	this->resourceQueue.push_back(&this->resourceList[itemIndex]);
	
	return this->resourceList[itemIndex];
}

/*Use to find resources*/
Resources ResourceManager::FindResource(ResourceName resourceName)
{

	return this->resourceList[static_cast<int>(resourceName)];
}

Resources ResourceManager::FindResource(int resourceName)
{

	return FindResource(static_cast<ResourceName>(resourceName));
}

Resources * ResourceManager::Find(ResourceName resourceName)
{
	return &this->resourceList[static_cast<int>(resourceName)];
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
	resources.update();
}

void ResourceManager::OnLoad()
{
	GameEngine::manager.inputManager.AddKey("IO", "i", "o");

	int randomInt = rand() % 100 + 1;

	Resources resource = AddResource(ResourceName::Null_Resource, "Null_Resource", "NULL", 1, 0, "Game/Assets/Textures/Resource/missing-16.png", 0, 1, 0, 0);
	resource = AddResource(ResourceName::Gold, "Gold", "GOLD", 1, 1, "Game/Assets/Textures/Resource/gold-16.png", 10000, 1, 0, 0);
	resource = AddResource(ResourceName::SpaceCow, "SpaceCow", "ANIMAL", 2750, 1000, "Game/Assets/Textures/Resource/cow-16.png", 100, randomInt, 1, 1);
	resource = AddResource(ResourceName::SpaceCow_Beef, "SpaceCow Beef", "MEAT", 75, 1000, "Game/Assets/Textures/Resource/steak-16.png", 100, randomInt, 1, 1);
	resource = AddResource(ResourceName::SpaceCow_Milk, "SpaceCow Milk", "DAIRY", 50, 1000, "Game/Assets/Textures/Resource/milk-16.png", 100, randomInt, 1, 1);
	resource = AddResource(ResourceName::SpaceCow_Cheese, "SpaceCow Cheese", "DAIRY", 10, 1000, "Game/Assets/Textures/Resource/cheese-16.png", 100, randomInt, 1, 1);
	resource = AddResource(ResourceName::Sheep, "Sheep", "ANIMAL", 1800, 1000, "Game/Assets/Textures/Resource/sheep-16.png", 100, randomInt, 1, 1);
	resource = AddResource(ResourceName::Sheep_Wool, "Sheep Wool", "MATERIAL", 30, 1000, "Game/Assets/Textures/Resource/wool-16.png", 100, randomInt, 1, 1);
	resource = AddResource(ResourceName::Sheep_Meat, "Sheep Meat", "MEAT", 150, 1000, "Game/Assets/Textures/Resource/mutton-16.png", 100, randomInt, 1, 1);
	resource = AddResource(ResourceName::Chicken, "Chicken", "ANIMAL", 800, 1000, "Game/Assets/Textures/Resource/livechicken-16.png", 100, randomInt, 1, 1);
	resource = AddResource(ResourceName::Chicken_Egg, "Chicken Egg", "EGGS", 10, 1000, "Game/Assets/Textures/Resource/egg-16.jpg", 100, randomInt, 1, 1);
	resource = AddResource(ResourceName::Chicken_Meat, "Chicken Meat", "MEAT", 50, 1000, "Game/Assets/Textures/Resource/chicken-16.png", 1000, randomInt, 1, 1);
	resource = AddResource(ResourceName::Kittain, "Kittain", "PET", 675, 1000, "Game/Assets/Textures/Resource/kittain-16.png", 100, randomInt, 1, 1);
	resource = AddResource(ResourceName::Doggo, "Doggo", "PET", 675, 1000, "Game/Assets/Textures/Resource/doggo-32.jpg", 100, randomInt, 1, 1);
	resource = AddResource(ResourceName::Steel_Cotton, "Steel Cotton", "MATERIAL", 30, 1000, "Game/Assets/Textures/Resource/steel_cotton-16.png", 1000, randomInt, 1, 1);
	resource = AddResource(ResourceName::Mandrake, "Mandrake", "PLANT", 150, 1000, "Game/Assets/Textures/Resource/mandrake-16.png", 100, randomInt, 1, 1);
	resource = AddResource(ResourceName::Grape, "Grape", "PLANT", 30, 1000, "Game/Assets/Textures/Resource/grape-16.png", 100, randomInt, 1, 1);
	resource = AddResource(ResourceName::Wine, "Wine", "FLUID", 150, 1000, "Game/Assets/Textures/Resource/wine-16.png", 100, randomInt, 1, 1);
	resource = AddResource(ResourceName::Unilateralis, "Unilateralis", "FUNGI", 30, 1000, "Game/Assets/Textures/Resource/unilateralis-16.png", 10000, randomInt, 1, 1);
	resource = AddResource(ResourceName::Electronic_Component, "Electronic Component", "MATERIAL", 150, 1000, "Game/Assets/Textures/Resource/component-16.png", 1000, randomInt, 1, 1);

}

int ResourceManager::NumberOfActiveResources()
{
	int count = 0;
	for (int i = 1; i <= this->itemIndex; i++) {
		count++;
	}
	return count;
}

int ResourceManager::RandomResources()
{
	int numberOfResources = NumberOfActiveResources();
	int generatedResourceID = (rand() % numberOfResources) + 1;
	return generatedResourceID;
}

list<Resource*> ResourceManager::GetList() const
{
	return resourceQueue;
}
