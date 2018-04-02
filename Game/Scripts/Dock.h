#pragma once
#include "Structure.h"
#include "GameManager.h"
#include "ContractManager.h"
#include "task_system\Task.h"


class Dock : public Structure
{
public:
	static Dock * Create();
	void Copy(GameObject * copyObject);
	void Update();

	void DockShip(class TradeShip* ship);
	vec3 ParkingLocation();
private:
	ContractManager * contractManager;
	Contract *contract;
	const Hub * hub;
	bool contractFufilled = true;

	v1::TaskSystem::Task flushTask;

	bool docked = false;
	class TradeShip *dockedShip;

	//Debug timer
	Engine::Utility::Clock timer;
};