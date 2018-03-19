#pragma once
#include "ResourceManager.h"
#include <list>

enum class MarketName {
	Null_Market,
	Local,
	Galactic
};

class LocalMarket {
public:
	LocalMarket();
	LocalMarket(MarketName marketName, ResourceManager* resourceManager);
	LocalMarket(const LocalMarket &copy);
	~LocalMarket();

	int GetCurrentPrice(ResourceName resourceName);
	void SetNewCurrentPrice(ResourceName resourceName);

	Resources AddResourceForSale(ResourceName resourceName);
	Resources FindResourceForSale(ResourceName resourceName);
	
	MarketName GetMarketID();
	int GetModifier(ResourceName resourceName); // Gets resouce demand to calc modifier
	void SetModifier(ResourceName resourceNAme); // Sets resource demand using modifier

	void OnLoad();
	void Start();
	void Update();


private:
	int marketID;
	ResourceManager* resourceManager;
	MarketName marketName;
	int modifier = 1;
	int resourceID;

	list <Resources> resourceForSale;
};

using Market = LocalMarket;