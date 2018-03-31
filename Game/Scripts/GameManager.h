#pragma once
#include "components\Behaviour.h"
#include "BuildingManager.h"
#include "ResourceManager.h"
#include "ContractManager.h"
#include "PlayerEconManager.h"
#include "MarketManager.h"
#include "Hub.h"

class GameManager : public Behaviour
{
public:
	static GameManager* Create(GameObject * gameObject);
	void Copy(GameObject *copyObject);

	void OnLoad();
	void Start();
	void Update();

	void SetHub(Hub *hub);
	Hub * GetHub() const;
	

	BuildingManager buildingManager;
	ResourceManager resourceManager;
	ContractManager contractManager;
	PlayerEconManager playerEconManager;
	MarketManager marketManager;

	static GameManager *gameManager;
private:
	Hub * hub;
};