#include "MarketManager.h"
#include "core\GameEngine.h"
#include "core\InputManager.h"
#include "utility\Clock.h"

MarketManager::MarketManager()
{
}

MarketManager::~MarketManager()
{
}

LocalMarket MarketManager::AddMarket(MarketName marketName, string nameOfMarket)
{
	LocalMarket localMarket = LocalMarket(marketName, resourceManager, nameOfMarket);

	switch (marketName) {
	case MarketName::Local:
		this->marketQueue[LOCAL] = localMarket;
		break;

	case MarketName::Galactic:
		this->marketQueue[GALACTIC] = localMarket;
		break;
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

LocalMarket * MarketManager::FindPersistentMarket(MarketName marketName)
{

	switch (marketName) {
	case MarketName::Local:
		return &marketQueue[LOCAL];

	case MarketName::Galactic:
		return &marketQueue[GALACTIC];

	default:
		return nullptr;
	}
}

void MarketManager::AddResource(MarketName marketToAddTo, ResourceName resourceName)
{
	// Need to add resource to correct market

	Resource resource = *resourceManager->Find(resourceName);

	if (marketToAddTo == MarketName::Local) {
		//cout << "Adding resource to... " << marketQueue[LOCAL].GetNameOfMarket() << endl;
		marketQueue[LOCAL].AddResource(resourceName);
		FindResourceForSale(marketToAddTo, resourceName);
		//cout << "TASK COMPLETED" << endl << endl;
	}

	if (marketToAddTo == MarketName::Galactic) {
		//cout << "Adding resource to... " << marketQueue[GALACTIC].GetNameOfMarket() << endl;
		marketQueue[GALACTIC].AddResource(resourceName);
		FindResourceForSale(marketToAddTo, resourceName);
		//cout << "TASK COMPLETED" << endl << endl;
	}
	
}

void MarketManager::FindResourceForSale(MarketName marketToSearch, ResourceName resourceName)
{
	// Need to check resource in correct market

	if (marketToSearch == MarketName::Local) {
		//cout << "Searching... " << marketQueue[LOCAL].GetNameOfMarket() << endl;
		marketQueue[LOCAL].FindResourceForSale(resourceName);
	}

	if (marketToSearch == MarketName::Galactic) {
		//cout << "Searching... " << marketQueue[GALACTIC].GetNameOfMarket() << endl;
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

	marketQueue.resize(2);
	AddMarket(MarketName::Local, "LOCAL_MARKET");
	AddResource(MarketName::Local, ResourceName::SpaceCow_Beef);
	AddResource(MarketName::Local, ResourceName::SpaceCow_Cheese);
	AddResource(MarketName::Local, ResourceName::SpaceCow_Milk);
	AddResource(MarketName::Local, ResourceName::Sheep_Wool);
	AddResource(MarketName::Local, ResourceName::Sheep_Meat);
	AddResource(MarketName::Local, ResourceName::Chicken_Egg);
	AddResource(MarketName::Local, ResourceName::Chicken_Meat);

	AddMarket(MarketName::Galactic, "GALACTIC_MARKET");
	AddResource(MarketName::Galactic, ResourceName::Kittain);
	AddResource(MarketName::Galactic, ResourceName::Steel_Cotton);
	AddResource(MarketName::Galactic, ResourceName::Mandrake);
	AddResource(MarketName::Galactic, ResourceName::Grape);
	AddResource(MarketName::Galactic, ResourceName::Wine);
	AddResource(MarketName::Galactic, ResourceName::Unilateralis);
	AddResource(MarketName::Galactic, ResourceName::Electronic_Component);

	marketQueue[LOCAL];
}

void MarketManager::Update()
{
	clock.UpdateClock();
	if (clock.Alarm()) {
		
	/*	for (int i = 0; i < marketQueue[LOCAL].GetResourceForSaleSize(); i++) {
			marketQueue[LOCAL].ChangeOverTimeOf(i, 25, 10);
		}
		
		for (int i = 0; i < marketQueue[LOCAL].GetResourceForSaleSize(); i++) {
			marketQueue[GALACTIC].ChangeOverTimeOf(i, 25, 10);
		}*/
		clock.ResetClock();
	}
	
}

vector<LocalMarket*> MarketManager::GetList() const
{
	return vector<LocalMarket*>();
}
