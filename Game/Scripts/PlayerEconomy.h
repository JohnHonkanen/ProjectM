#pragma once

#include "ResourceManager.h"
#include "ContractManager.h"

using namespace std;

class PlayerEconomy {
public:
	PlayerEconomy();
	~PlayerEconomy();
	
	void GiveGoldBars(int amountToGive);
	void AddGoldBars(int goldBars);
	void RemoveGoldBars(int goldBars);
	int GetGBAmount(int GBAmount);

	void Init();
private:
	int goldBars;
	Resources resource;
	Contract contract;
};