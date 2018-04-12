#pragma once
#include "components\Behaviour.h"
#include "BuildingManager.h"
#include "ResourceManager.h"
#include "ContractManager.h"
#include "PlayerEconManager.h"
#include "MarketManager.h"
#include "Hub.h"
#include "RecipeManager.h"
#include "DayNightCycle.h"

class GameManager : public Behaviour
{
public:
	static GameManager* Create(GameObject * gameObject);
	void Copy(GameObject *copyObject);

	void OnLoad();
	void Start();
	void Update();
	void Update(double dt);

	/** Get and Set the Hub*/
	void SetHub(Hub *hub);
	Hub * GetHub() const;

	/** Get and Set the TradeShip Spawner*/
	void SetTradeShipSpawner(class TradeShipSpawner *spawner);
	class TradeShipSpawner * GetTradeShipSpawner() const;
	bool mouseOverHudElement = false;

	/** Managers in the game*/
	BuildingManager buildingManager;
	ResourceManager resourceManager;
	ContractManager contractManager;
	PlayerEconManager playerEconManager;
	MarketManager marketManager;
	RecipeManager recipeManager;
	DayNightCycle dayNightCycle;
	static GameManager *gameManager;
private:
	Hub * hub;
	class TradeShipSpawner * tradeShipSpawner;
};