#include "LocalMarket.h"

LocalMarket::LocalMarket()
{
}

LocalMarket::LocalMarket(ResourceManager * resourceManager)
{
	this->resourceManager = resourceManager;
}

LocalMarket::~LocalMarket()
{
}

void LocalMarket::OnLoad()
{
}

void LocalMarket::Start()
{
	clock.SetDelay(5000);
	clock.StartClock();
}

void LocalMarket::Update()
{
	clock.UpdateClock();

	if (clock.Alarm()) {

	} 
	clock.ResetClock();
}
