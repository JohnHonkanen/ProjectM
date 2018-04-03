#pragma once

#include "ResourceManager.h"
#include "PlayerEconomy.h"
#include "ContractManager.h"
#include "InventoryV2.h"

#include "components\Behaviour.h"
#include "core\GameObject.h"
#include <vector>
#include "utility\Clock.h"

#define PLAYER_ECON 0 

class PlayerEconManager : public Behaviour{
public:
	PlayerEconManager();
	~PlayerEconManager();

	PlayerEconomy AddEconomy(EconName econName, string nameOfEconomy);
	PlayerEconomy* FindPlayerEcon(EconName econName); // Finds the player economy
	void SetResourceManager(ResourceManager* resourceManager);

	static PlayerEconManager* Create(GameObject *gameObject);
	void Copy(GameObject *copyObject);

	void OnLoad();
	void Update();
	void Start();

	void SetHUBInventory(v2::Inventory* HUBInventory);
	v2::Inventory* GetHUBInventory(); // Get Hub inventory

	int GetCurrentGoldAmountIn(v2::Inventory* inventory); // Get current gold amount in the inventory
	int GetCurrentDebtAmount(); // Get Get current debt levels
	void AddInterestToDebt(int amount); // Add amount of interest to debt 
	void CheckIfPlayerInDebt(); // Method to check debt status of player + does actions
	bool IsInDebt(); // Returns if in debt

	void AdjustInterest(int amount); // Increase/Decrease interest 
	int CalculateInterest();
	int GetInterest(); // Get interest + calculate
	void SetInterest(int amount); // Set the interest 

	void ReduceProductionLevel(); // Set Dome and factory production efficiency to 1

	v2::Inventory* HUBInventory;
	vector <PlayerEconomy*> GetList() const;
private:
	bool inDept = false;
	int interestAmount;
	float defaultInterestPercentage = 0.001;
	vector<PlayerEconomy> econList;
	ResourceManager* resourceManager;
	PlayerEconomy playerEconomy;
	ContractManager* contractManager;

	Engine::Utility::Clock clock;
};