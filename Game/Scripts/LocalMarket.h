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

	vector<Resources> GetResources() const;
private:
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