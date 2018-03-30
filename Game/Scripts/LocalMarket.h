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

	int GetCurrentPrice(ResourceName resourceName);
	void SetNewCurrentPrice(ResourceName resourceName);
	MarketName GetMarketID();
	string GetNameOfMarket();
	
	Resources AddResource(ResourceName resourceName); // Add Resource that can be sold in the market
	bool FindResourceForSale(ResourceName resourceName); // Find if resource is for sale

	string GetResourceIcon(ResourceName resourceName); // Get Resource Icon for item sold in market
	int GetResourcePrice(ResourceName resourceName); // Get Resource price
	int GetModifier(ResourceName resourceName); // Gets resouce demand to calc modifier
	void SetModifier(ResourceName resourceNAme); // Sets resource demand using modifier

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
private:
	static const int MAX_LIMITER = 95;
	static const int MIN_LIMITER = 1;
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