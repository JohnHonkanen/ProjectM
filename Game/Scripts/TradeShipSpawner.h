#pragma once
#include "components\Behaviour.h"
#include <vector>

class TradeShip : public Behaviour {
public:
	static TradeShip *Create(GameObject *gameObject);
	void Copy(GameObject * gameObject);
};

class TradeShipSpawner : public Behaviour
{
public:
	static TradeShipSpawner *Create(GameObject *gameObject);
	~TradeShipSpawner();
	void Copy(GameObject * gameObject);
	void OnLoad();
	void Update(double dt);

	void CreateTradeShips();
private:
	TradeShip * prefab;
	vector<TradeShip*> tradeShips;
	vector<vector<TradeShip>::iterator> completedTradeShips;
};