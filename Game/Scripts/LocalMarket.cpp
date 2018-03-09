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

int LocalMarket::GetCurrentPrice(ResourceName resourceName)
{
	return resourceManager->Find(resourceName)->GetBasePrice();
}

void LocalMarket::SetNewCurrentPrice(ResourceName resourceName)
{
	int current = GetCurrentPrice(resourceName);

	int newPrice = current + GetModifier();

	resourceManager->Find(resourceName)->SetBasePrice(newPrice);
}


int LocalMarket::GetModifier()
{
	return 0;
}

void LocalMarket::SetModifier()
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
