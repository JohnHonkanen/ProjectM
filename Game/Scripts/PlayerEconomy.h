#pragma once
#include "ResourceManager.h"

#include <string>

using namespace std;

class PlayerEconManager;
class PlayerEconomy {
public:
	PlayerEconomy();
	PlayerEconomy(Resources resource, PlayerEconManager* playerEconManager);
	~PlayerEconomy();
	

	void GiveGoldBars(int amountToGive);
	void AddGoldBars(int goldBars);
	void RemoveGoldBars(int goldBars);
	int GetGBAmount(int GBAmount);

	Resources GetResouce();
	string GetGBIcon(); // Get the gold bar icon

	void Init();
private:
	int goldBars;

	Resources resource;
	ResourceManager* resourceManager;;
	PlayerEconManager* playerEconManager;
};