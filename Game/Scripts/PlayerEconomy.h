#pragma once

#include "ResourceManager.h"


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
};