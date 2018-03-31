#pragma once
#include "ResourceManager.h"
#include <vector>
#include <string>

enum class MarketName {
	Null_Market,
	Local,
	Galactic
};

class LocalMarket {
public:
	LocalMarket();
	LocalMarket(MarketName marketName, ResourceManager* resourceManager, string nameOfMarket);
	LocalMarket(const LocalMarket &copy);
	~LocalMarket();

	MarketName GetMarketID();
	string GetNameOfMarket();
	
	Resources AddResource(ResourceName resourceName); // Add Resource that can be sold in the market
	bool FindResourceForSale(ResourceName resourceName); // Find if resource is for sale

	string GetResourceIcon(ResourceName resourceName); // Get Resource Icon for item sold in market

	int GetResourceForSaleSize();

	void OnLoad();
	void Start();
	void Update();

	vector<Resources> &GetResources();
	int GetBasePriceOf(int index); // Get Base price of resource at vector index
	void SetBasePriceOf(int index, int price); // Set Base price of resource at vector index.
	void IncreaseBasePriceOf(int index, int price); // Increase Base price of resource at vector index
	void DecreaseBasePriceOf(int index, int price); // Decrease Base price of resource at vector index

	int GetItemStock(int index); // Get item stock at vector index
	void IncreaseItemStock(int index, int amount); // Increase Item stock amount at vector index
	void DecreaseItemStock(int index, int amount); // Decrease Item stock amount at vector index

	string GetNameOfItem(int index); // Get name of Item 

	int GetDemandOf(int index); // Get Demand of item at vector index
	void IncreaseDemandOf(int index, int amount); // Increase Demand of item at vector index
	void DecreaseDemandOf(int index, int amount); // Decrease Demand of item at vector index

private:
	static const int MAX_LIMITER = 1000;
	static const int MIN_LIMITER = 0;
	int marketID;
	Resources resource;
	ResourceManager* resourceManager;
	MarketName marketName;
	int modifier = 1;
	int resourceID, basePrice;
	string nameOfMarket;

	vector<Resources> resourceForSale;
};

using Market = LocalMarket;