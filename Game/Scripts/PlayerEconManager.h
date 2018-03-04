#pragma once
#include "PlayerEconomy.h"
#include "ContractManager.h"
#include "ResourceManager.h"

class PlayerEconManager {
public:
	PlayerEconManager();
	~PlayerEconManager();

	PlayerEconomy AddEconomy();
	PlayerEconomy* FindPlayerEcon(); // Finds the player economy

	void SetResourceManager(ResourceManager* resourceManager);
	void Update();
	void Start();

private:

	PlayerEconomy economyList[3]; // List of economies
	PlayerEconomy* playerEconomy;
	ResourceManager* resourceManager;

};