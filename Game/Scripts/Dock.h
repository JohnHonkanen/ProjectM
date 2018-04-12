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

	/** Docks the trade ship and set up all the links correctly*/
	void DockShip(class TradeShip* ship);
	/** Get the location for drone parking*/
	vec3 ParkingLocation();

	/** Generate Configurations for various markets*/
	void GenerateContractConfiguration();
	void GenerateLocalMarketConfiguration();
	void GenerateGalacticMarketConfiguration();

	void AddToMarketDump(ResourceName resourceName, int amountToDump); // Adds items to marketdump (BUY FROM MARKET)
	void AddToMarketRequest(ResourceName resourceName, int amountToRequest); // Adds items to marketRequest (SELL TO MARKET)

	/**Complete the held contract*/
	void CompleteContract();
	void TaskCompleted(TASK_TYPE type, int index); //@Override
	int Collect(ResourceName resourceName, int resourceAmount, int index); //@Override
	int Deposit(ResourceName resourceName, int resourceAmount, int index); //@Override
	void IncreaseTaskNumber(TASK_TYPE type, int index); //@Override
	void SetDockDestoryed(bool state) { dockDestroyed = state; }
	bool GetDockDestoryed() { return dockDestroyed; }
	void AddInboundShip(class TradeShip* ts);
	
private:
	void MarketDumpTaskee(); // Generate task for market dump
	void BufferMarket(); // Does magic with inventory

	ContractManager * contractManager;
	int contractID;
	int contractIndex;
	const Hub * hub;
	bool contractFufilled = true;

	v1::TaskSystem::Task marketTask;
	v1::TaskSystem::Task marketRequestTask;
	v2::Inventory marketDump; // Marketplace item inventory
	v2::Inventory marketRequest; // Marketplace inventory of items asking from system
	v2::Inventory marketPlaceBuffer; // Marketplace buffer inventory

	bool docked = false;
	bool dockDestroyed = false;
	class TradeShip *dockedShip;
	DockName dockName;
	//Debug timer
	Engine::Utility::Clock timer;

	int numMarketTask = 0;
	int maxMarketTask = 1;
	int numMarketRequestTask = 0;
	int maxMarketRequestTask = 1;
	int numTask = 0;
	int maxTask = 1;
};