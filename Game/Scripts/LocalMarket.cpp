#include "LocalMarket.h"

LocalMarket::LocalMarket()
{
}

LocalMarket::LocalMarket(MarketName marketName)
{
	this->marketID = static_cast<int>(marketName);
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

	int newPrice = current + GetModifier(resourceName);

	cout << "Old: " << GetCurrentPrice(resourceName) << endl;

	resourceManager->Find(resourceName)->SetBasePrice(newPrice);

	cout << "New: " << GetCurrentPrice(resourceName) << endl;
}


int LocalMarket::GetModifier(ResourceName resourceName)
{
	return resourceManager->Find(resourceName)->GetDemand();
}

void LocalMarket::SetModifier(ResourceName resourceName)
{
	// WIP: Add conditional statement:  If purchase, then increase modifier else, decrease.

	int currentDemand = GetModifier(resourceName);

	int newDemand = currentDemand + modifier;

	resourceManager->Find(resourceName)->SetDemand(newDemand);
}

void LocalMarket::OnLoad()
{
}

void LocalMarket::Start()
{

}

void LocalMarket::Update()
{

}
