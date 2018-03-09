#include "MarketManager.h"
#include "core\GameEngine.h"
#include "core\InputManager.h"

MarketManager::MarketManager()
{
}

MarketManager::~MarketManager()
{
}

LocalMarket MarketManager::AddMarket(ResourceManager* resourceManager, MarketName marketName)
{
	this->localMarket = LocalMarket(resourceManager, marketName);
	this->marketID = static_cast<int>(marketName);

	this->marketList[marketID] = this->localMarket;
	this->marketQueue.push_back(&this->marketList[marketID]);

	return marketList[marketID];
}

LocalMarket * MarketManager::Find()
{
	return nullptr;
}

MarketManager * MarketManager::Create(GameObject *gameObject)
{
	MarketManager *m = new MarketManager();
	gameObject->AddComponent(m);
	return m;
}

void MarketManager::Copy(GameObject * copyObject)
{
	// Do nothing
}

void MarketManager::OnLoad()
{
	AddMarket();
}

void MarketManager::Start()
{
	clock.SetDelay(5000);
	clock.StartClock();
}

void MarketManager::Update()
{
	clock.UpdateClock();

	if (clock.Alarm()) {

	}
	clock.ResetClock();
}

list<LocalMarket*> MarketManager::GetList() const
{
	return list<LocalMarket*>();
}
