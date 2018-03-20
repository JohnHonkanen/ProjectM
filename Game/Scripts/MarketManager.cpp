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

void MarketManager::AddResource(MarketName marketToAddTo, ResourceName resourceName)
{
	// Need to add resource to correct market

	Resource resource = *resourceManager->Find(resourceName);

	if (marketToAddTo == MarketName::Local) {
		cout << "Adding resource to... " << marketQueue[LOCAL].GetNameOfMarket() << endl;
		marketQueue[LOCAL].AddResource(resourceName);
		FindResourceForSale(marketToAddTo, resourceName);
		cout << "TASK COMPLETED" << endl << endl;
	}

	if (marketToAddTo == MarketName::Galactic) {
		cout << "Adding resource to... " << marketQueue[GALACTIC].GetNameOfMarket() << endl;
		marketQueue[GALACTIC].AddResource(resourceName);
		FindResourceForSale(marketToAddTo, resourceName);
		cout << "TASK COMPLETED" << endl << endl;
	}
	
}

void MarketManager::FindResourceForSale(MarketName marketToSearch, ResourceName resourceName)
{
	// Need to check resource in correct market

	if (marketToSearch == MarketName::Local) {
		cout << "Searching... " << marketQueue[LOCAL].GetNameOfMarket() << endl;
		marketQueue[LOCAL].FindResourceForSale(resourceName);
	}

	if (marketToSearch == MarketName::Galactic) {
		cout << "Searching... " << marketQueue[GALACTIC].GetNameOfMarket() << endl;
		marketQueue[GALACTIC].FindResourceForSale(resourceName);
	}

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
	AddResource(MarketName::Galactic, ResourceName::Chicken_Meat);
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
