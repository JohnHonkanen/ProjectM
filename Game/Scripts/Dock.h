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
private:
	ContractManager * contractManager;
	Contract *contract;
	int contractID;
	const Hub * hub;
	bool contractFufilled = true;

	v1::TaskSystem::Task flushTask;

	bool docked = false;
	class TradeShip *dockedShip;
	DockName dockName;
	//Debug timer
	Engine::Utility::Clock timer;
};