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

	resourceForSale[index].DecreaseItemBasePrice(price);

	if (resourceForSale[index].GetBasePrice() <= MIN_LIMITER) {
		resourceForSale[index].SetBasePrice(1);
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
	resourceForSale[index].ReduceItemAmount(amount);

	if (resourceForSale[index].GetItemAmount() <= MIN_LIMITER) {
		resourceForSale[index].SetItemAmount(MIN_LIMITER);
	}
}

string LocalMarket::GetNameOfItem(int index)
{
	return resourceForSale[index].GetName();
}

int LocalMarket::GetDemandOf(int index)
{
	return resourceForSale[index].GetDemand();
}

void LocalMarket::IncreaseDemandOf(int index, int amount)
{
	resourceForSale[index].IncreaseDemand(amount);
}

void LocalMarket::DecreaseDemandOf(int index, int amount)
{
	resourceForSale[index].DecreaseDemand(amount);
}

void LocalMarket::ChangeOverTimeOf(int index, int demand, int price)
{
	int randomInt = rand() % 10;
	if (randomInt > 5) {
		IncreaseBasePriceOf(index, price + randomInt);
		IncreaseDemandOf(index, demand + randomInt);
		IncreaseItemStock(index, demand + randomInt);
	} else if (randomInt < 5) {
		DecreaseBasePriceOf(index, price + randomInt);
		DecreaseDemandOf(index, demand + randomInt);
		DecreaseItemStock(index, demand + randomInt);
	}
}

