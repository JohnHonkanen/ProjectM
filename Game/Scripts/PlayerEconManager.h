#pragma once

#include "ResourceManager.h"
#include "PlayerEconomy.h"

class PlayerEconManager {
public:
	PlayerEconManager();
	~PlayerEconManager();

	PlayerEconomy AddEconomy();
	PlayerEconomy* FindPlayerEcon(); // Finds the player economy
	void SetResourceManager(ResourceManager* resourceManager);
	
	void OnLoad();
	void Update();
	void Start();


private:
	
	PlayerEconomy economyList[3]; // List of economies
	ResourceManager* resourceManager;

};