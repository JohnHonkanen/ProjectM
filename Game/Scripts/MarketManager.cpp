#include "MarketManager.h"
#include "core\GameEngine.h"
#include "core\InputManager.h"

MarketManager::MarketManager()
{
}

MarketManager::~MarketManager()
{
}

LocalMarket MarketManager::AddMarket(MarketName marketName, string nameOfMarket)
{
	LocalMarket localMarket = LocalMarket(marketName, resourceManager, nameOfMarket);

	// Check if market exists

	if (Find(marketName).GetMarketID() == MarketName::Null_Market) {
		this->marketQueue.push_back(localMarket);
	}

	return localMarket;
}

LocalMarket MarketManager::Find(MarketName marketName)
{
	bool found = false;
	for (auto availableMarket : marketQueue) {
		if (availableMarket.GetMarketID() == marketName) {
			found = true;
			return availableMarket;
		}
	}
	if (!found) {
		return LocalMarket();
	}
}

Resources MarketManager::AddResource(MarketName marketToAddTo, ResourceName resourceName)
{
	// Need to add resource to correct market

	Resource resource = *resourceManager->Find(resourceName);

	// Check if resource exists in resourceForSale list

	if (FindResourceForSale(marketToAddTo, resourceName).GetResouceID() != ResourceName::Null_Resource) {
		this->resourceForSale.push_back(resource);
	}

	return resource;
}

Resources MarketManager::FindResourceForSale(MarketName marketToSearch, ResourceName resourceName)
{
	// Need to check resource in correct market

	bool found = false;
	Resource resource = *resourceManager->Find(resourceName);

	// Check if resource exists in resourceForSale list
	for (auto res : resourceForSale) {
		if (res.GetResouceID == resourceName) {
			found = true;
			return res;
		}
	}

	// Need a return statement if not found
}

MarketManager * MarketManager::Create(GameObject *gameObject)
{
	MarketManager *m = new MarketManager();
	gameObject->AddComponent(m);
	return m;
}

void MarketManager::SetResourceManager(ResourceManager * resourceManager)
{
	this->resourceManager = resourceManager;
}

void MarketManager::Copy(GameObject * copyObject)
{
	// Do nothing
}

void MarketManager::OnLoad()
{

}

void MarketManager::Start()
{
	clock.SetDelay(5000);
	clock.StartClock();

	AddMarket(MarketName::Local, "LOCAL_MARKET");
	AddResource(MarketName::Local, ResourceName::Chicken_Egg);

	AddMarket(MarketName::Galactic, "GALACTIC_MARKET");
	AddResource(MarketName::Local, ResourceName::Chicken_Meat);

	Find(MarketName::Galactic).GetNameOfMarket();
}

void MarketManager::Update()
{
	clock.UpdateClock();
	//marketQueue[LOCAL].SetNewCurrentPrice(ResourceName::Chicken_Egg);
	if (clock.Alarm()) {
		
		
		clock.ResetClock();
	}
	
}

vector<LocalMarket*> MarketManager::GetList() const
{
	return vector<LocalMarket*>();
}
