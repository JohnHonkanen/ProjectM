#pragma once
#include "components\Behaviour.h"
#include <vector>
#include "Dock.h"

class TradeShip : public Behaviour {
public:
	static TradeShip *Create(GameObject *gameObject);
	void Copy(GameObject * gameObject);
	void SetDock(Dock *dock);

	void Update(double dt);
private:
	void RotateToFaceDock();
	Dock * dock;
	float speed = 100.0f;
	float currentSpeed = 100.0f;
	bool landed = false;
	float rotYOffset = 0;
};

class TradeShipSpawner : public Behaviour
{
public:
	static TradeShipSpawner *Create(GameObject *gameObject);
	~TradeShipSpawner();
	void Copy(GameObject * gameObject);
	void OnLoad();
	void Update();

	void CreateTradeShip(Dock *dock);
private:
	TradeShip * prefab;
	vector<TradeShip*> tradeShips;
	vector<vector<TradeShip>::iterator> completedTradeShips;
};