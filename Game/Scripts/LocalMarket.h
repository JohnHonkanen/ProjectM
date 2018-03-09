#pragma once
#include "ResourceManager.h"

enum class MarketName {
	local,
	galactic
};

class LocalMarket {
public:
	LocalMarket();
	LocalMarket(MarketName marketName);
	~LocalMarket();

	int GetCurrentPrice(ResourceName resourceName);
	void SetNewCurrentPrice(ResourceName resourceName);

	int GetModifier(ResourceName resourceName); // Gets resouce demand to calc modifier
	void SetModifier(ResourceName resourceNAme); // Sets resource demand using modifier

	void OnLoad();
	void Start();
	void Update();


private:
	int marketID;
	ResourceManager* resourceManager;

	int modifier = 1;
};