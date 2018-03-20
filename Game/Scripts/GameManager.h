#pragma once
#include "components\Behaviour.h"
#include "BuildingManager.h"
#include "ResourceManager.h"
#include "ContractManager.h"
#include "PlayerEconManager.h"
#include "MarketManager.h"

class GameManager : public Behaviour
{
public:
	static GameManager* Create(GameObject * gameObject);
	void Copy(GameObject *copyObject);

	void OnLoad();
	void Start();
	void Update();
	

	BuildingManager buildingManager;
	ResourceManager resourceManager;
	ContractManager contractManager;
	PlayerEconManager playerEconManager;
	MarketManager marketManager;
	
};