#pragma once
#include "ResourceManager.h"
#include "Inventory.h"

#include <string>

using namespace std;

class PlayerEconManager;
class PlayerEconomy {
public:
	PlayerEconomy();
	PlayerEconomy(ResourceManager* resourceManager, PlayerEconManager* playerEconManager);
	~PlayerEconomy();
	

	void GiveGoldBars(int amountToGive);
	void AddGoldBars(int goldBars);
	void RemoveGoldBars(int goldBars);
	int GetGBAmount();
	void SetGBAmount(int GBAmount);

	Resources GetResouce();
	string GetGBIcon(); // Get the gold bar icon

	void StoreGold(Resources resourceToStore);

	std::string name;
private:
	Resources resource;
	ResourceManager* resourceManager;
	PlayerEconManager* playerEconManager;
	Inventory inventory;

//protected:
//	std::unique_ptr<Inventory> inventory = std::make_unique<Inventory>();
};