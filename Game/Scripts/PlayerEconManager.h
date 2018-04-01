#pragma once

#include "ResourceManager.h"
#include "PlayerEconomy.h"
#include "ContractManager.h"
#include "InventoryV2.h"

#include "components\Behaviour.h"
#include "core\GameObject.h"
#include <vector>

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
	
	v2::Inventory* HUBInventory;
	vector <PlayerEconomy*> GetList() const;
private:
	vector<PlayerEconomy> econList;
	ResourceManager* resourceManager;
	PlayerEconomy playerEconomy;
	ContractManager* contractManager;
};