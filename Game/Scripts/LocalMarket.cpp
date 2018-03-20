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
	return this->basePrice = resourceManager->Find(resourceName)->GetBasePrice();
}

void LocalMarket::SetNewCurrentPrice(ResourceName resourceName)
{
	int current = GetCurrentPrice(resourceName);

	int newPrice = current + GetModifier(resourceName);

	if (resourceManager->Find(resourceName)->GetResouceID() != ResourceName::Null_Resource) {
		cout << "Old: " << GetCurrentPrice(resourceName) << endl;
		resourceManager->Find(resourceName)->SetBasePrice(newPrice);
		cout << "New: " << GetCurrentPrice(resourceName) << endl;
	}

	if (resourceManager->Find(resourceName)->GetResouceID() == ResourceName::Null_Resource) {
		cout << "Whoops! We just tried to SetNewCurrentPrice on a Null_Resource!" << endl;
	}
}

string LocalMarket::GetNameOfMarket()
{
	return this->nameOfMarket;
}

Resources LocalMarket::AddResource(ResourceName resourceName)
{
	Resource resource = *resourceManager->Find(resourceName);
	// Check if resource exists in resourceForSale list

	if (resourceName != ResourceName::Null_Resource) {
		this->resourceForSale.push_back(resource);
	}

	return resource;
}

bool LocalMarket::FindResourceForSale(ResourceName resourceName)
{
	Resource resource = *resourceManager->Find(resourceName);
	
	bool found = false;

	for (auto res : resourceForSale) {
		if (res.GetResouceID() == resourceName) {
			found = true;
			cout << "Resource (duplicate) found" << endl;
			return found;
		}
	}
	cout << "Resource (duplicate) not found" << endl;
	return found;
}

MarketName LocalMarket::GetMarketID()
{
	return this->marketName;
}

string LocalMarket::GetResourceIcon(ResourceName resourceName)
{
	Resource resource = *resourceManager->Find(resourceName);
	return resource.GetResourceIcon();
}

int LocalMarket::GetResourcePrice(ResourceName resourceName)
{
	Resource resource = *resourceManager->Find(resourceName);
	return resource.GetBasePrice();
}

int LocalMarket::GetModifier(ResourceName resourceName)
{
	Resource resource = *resourceManager->Find(resourceName);
	return resource.GetDemand();
}

void LocalMarket::SetModifier(ResourceName resourceName)
{
	// WIP: Add conditional statement:  If purchase, then increase modifier else, decrease.

	int currentDemand = GetModifier(resourceName);

	int newDemand = currentDemand + modifier;

	resourceManager->Find(resourceName)->SetDemand(newDemand);
}

int LocalMarket::GetResourceForSaleSize()
{
	return resourceForSale.size();
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

vector<Resources> LocalMarket::GetResources() const
{
	return resourceForSale;
}
