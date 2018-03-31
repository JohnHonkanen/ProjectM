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
			return found;
		}
	}
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

vector<Resources> &LocalMarket::GetResources()
{
	return resourceForSale;
}

int LocalMarket::GetBasePriceOf(int index)
{

	return resourceForSale[index].GetBasePrice();
}

void LocalMarket::SetBasePriceOf(int index, int price)
{
	resourceForSale[index].SetBasePrice(price);
}

void LocalMarket::IncreaseBasePriceOf(int index, int price)
{
	resourceForSale[index].IncreaseItemBasePrice(price);
}

void LocalMarket::DecreaseBasePriceOf(int index, int price)
{
	if (resourceForSale[index].GetBasePrice() <= MIN_LIMITER) {
		resourceForSale[index].SetBasePrice(1);
	}
	else {
		resourceForSale[index].DecreaseItemBasePrice(price);
	}
}

int LocalMarket::GetItemStock(int index)
{
	return resourceForSale[index].GetItemAmount();
}

void LocalMarket::IncreaseItemStock(int index, int amount)
{
	resourceForSale[index].IncreaseItemAmount(amount);
}

void LocalMarket::DecreaseItemStock(int index, int amount)
{
	if (resourceForSale[index].GetItemAmount() <= MIN_LIMITER) {
		resourceForSale[index].SetItemAmount(MIN_LIMITER);
	}
	else {
		resourceForSale[index].ReduceItemAmount(amount);
	}
}

string LocalMarket::GetNameOfItem(int index)
{
	return resourceForSale[index].GetName();
}

