#include "LocalMarket.h"

LocalMarket::LocalMarket()
{
	this->marketName = MarketName::Null_Market;
}

LocalMarket::LocalMarket(MarketName marketName, ResourceManager* resourceManager, string nameOfMarket)
{
	this->marketName = marketName;
	this->resourceManager = resourceManager;
	this->nameOfMarket = nameOfMarket;
}

LocalMarket::LocalMarket(const LocalMarket & copy)
{
	this->marketName = copy.marketName;
	this->resourceManager = copy.resourceManager;
	this->nameOfMarket = copy.nameOfMarket;
}

LocalMarket::~LocalMarket()
{
}

int LocalMarket::GetCurrentPrice(ResourceName resourceName)
{
	this->basePrice = FindResourceForSale(resourceName).GetBasePrice();
	return this->basePrice;
}

void LocalMarket::SetNewCurrentPrice(ResourceName resourceName)
{
	int current = GetCurrentPrice(resourceName);

	int newPrice = current + GetModifier(resourceName);

	if (FindResourceForSale(resourceName).GetResouceID() != ResourceName::Null_Resource) {
		cout << "Old: " << GetCurrentPrice(resourceName) << endl;
		FindResourceForSale(resourceName).SetBasePrice(newPrice);
		cout << "New: " << GetCurrentPrice(resourceName) << endl;
	}

	if (FindResourceForSale(resourceName).GetResouceID() == ResourceName::Null_Resource) {
		cout << "Whoops! We just tried to SetNewCurrentPrice on a Null_Resource!" << endl;
	}
}

string LocalMarket::GetNameOfMarket()
{
	return this->nameOfMarket;
}

MarketName LocalMarket::GetMarketID()
{
	return this->marketName;
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
