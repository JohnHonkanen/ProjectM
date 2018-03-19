#include "MarketManager.h"
#include "core\GameEngine.h"
#include "core\InputManager.h"

MarketManager::MarketManager()
{
}

MarketManager::~MarketManager()
{
}

LocalMarket MarketManager::AddMarket(MarketName marketName)
{
	LocalMarket localMarket = LocalMarket(marketName, resourceManager);

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
		cout << "Market not found" << endl;
		return LocalMarket();
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

	AddMarket(MarketName::Local);
	marketQueue[LOCAL].Start();
	AddMarket(MarketName::Galactic);
	marketQueue[GALACTIC].Start();
}

void MarketManager::Update()
{
	clock.UpdateClock();
	marketQueue[LOCAL].SetNewCurrentPrice(ResourceName::Chicken_Egg);
	if (clock.Alarm()) {
		
		
		clock.ResetClock();
	}
	
}

vector<LocalMarket*> MarketManager::GetList() const
{
	return vector<LocalMarket*>();
}
