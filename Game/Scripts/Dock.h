#pragma once
#include "Structure.h"
#include "GameManager.h"
#include "ContractManager.h"
#include "task_system\Task.h"

enum class DockName {
	Contract,
	Local_Market,
	Galactic_Market
};

class Dock : public Structure
{
public:
	static Dock * Create();
	static Dock * Create(int upkeep, int cost);
	static Dock * Create(int upkeep, int cost, DockName dockName, string nameOfDock);

	void Copy(GameObject * copyObject);
	void Start();
	void Update();

	void DockShip(class TradeShip* ship);
	vec3 ParkingLocation();

	void GenerateContractConfiguration();
	void GenerateLocalMarketConfiguration();
	void GenerateGalacticMarketConfiguration();

	void AddToMarketDump(ResourceName resourceName, int amountToDump); // Adds items to marketdump (BUY FROM MARKET)
	void AddToMarketRequest(ResourceName resourceName, int amountToRequest); // Adds items to marketRequest (SELL TO MARKET)

	void TaskCompleted(TASK_TYPE type, int index); //@Override
	int Collect(ResourceName resourceName, int resourceAmount, int index); //@Override
	int Deposit(ResourceName resourceName, int resourceAmount, int index); //@Override
private:
	void MarketDumpTaskee(); // Generate task for market dump
	void BufferMarket(); // Does magic with inventory

	ContractManager * contractManager;
	Contract *contract;
	int contractID;
	const Hub * hub;
	bool contractFufilled = true;

	v1::TaskSystem::Task marketTask;
	v1::TaskSystem::Task marketRequestTask;
	v2::Inventory marketDump; // Marketplace item inventory
	v2::Inventory marketRequest; // Marketplace inventory of items asking from system
	v2::Inventory marketPlaceBuffer; // Marketplace buffer inventory

	bool docked = false;
	class TradeShip *dockedShip;
	DockName dockName;
	//Debug timer
	Engine::Utility::Clock timer;
};