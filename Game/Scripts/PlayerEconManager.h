#pragma once
#include "PlayerEconomy.h"
#include "ContractManager.h"


class PlayerEconManager {
public:
	PlayerEconManager();
	~PlayerEconManager();

	PlayerEconomy* FindPlayerEcon(); // Finds the player economy

private:

	PlayerEconomy* playerEconomy;
};