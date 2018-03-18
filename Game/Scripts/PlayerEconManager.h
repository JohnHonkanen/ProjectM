#pragma once

#include "ResourceManager.h"
#include "PlayerEconomy.h"
#include "ContractManager.h"
#include "InventoryV2.h"

#include "components\Behaviour.h"
#include "core\GameObject.h"

class PlayerEconManager : public Behaviour{
public:
	PlayerEconManager();
	~PlayerEconManager();

	PlayerEconomy AddEconomy();
	PlayerEconomy* FindPlayerEcon(); // Finds the player economy
	void SetResourceManager(ResourceManager* resourceManager);

	static PlayerEconManager* Create(GameObject *gameObject);
	void Copy(GameObject *copyObject);

	void OnLoad();
	void Update();
	void Start();

	void SetHUBInventory(v2::Inventory* HUBInventory);
	v2::Inventory* HUBInventory;
private:
	
	PlayerEconomy economyList[1]; // List of economies
	ResourceManager* resourceManager;
	PlayerEconomy playerEconomy;
	ContractManager* contractManager;

	
};