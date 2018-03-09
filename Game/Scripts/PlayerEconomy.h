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
	
	void GiveGoldBars(int amountToGive); // Give gold bars. <--- Deactivated
	void AddGoldBars(int goldBars); // Add gold bars
	void RemoveGoldBars(int goldBars); // Remove gold bars
	int GetGBAmount(); // Get gold bar amount
	void SetGBAmount(int GBAmount); // Set Gold Bar amount

	void SetPlayerEconIndex(int indexToSet); // Set pecon index 
	int GetPlayerEconIndex(); // Gets index of pecon

	Resources GetResouce(); // Gets resource
	string GetGBIcon(); // Get the gold bar icon

	std::string name;
private:
	int index = 0;
	Resources resource;
	ResourceManager* resourceManager;
	PlayerEconManager* playerEconManager;
	Inventory inventory;

};