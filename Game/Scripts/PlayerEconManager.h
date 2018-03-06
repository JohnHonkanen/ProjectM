#pragma once

#include "ResourceManager.h"
#include "PlayerEconomy.h"

#include "components\Behaviour.h"
#include "core\GameObject.h"

class PlayerEconManager : public Behaviour{
public:
	PlayerEconManager();
	~PlayerEconManager();

	PlayerEconomy AddEconomy();
	PlayerEconomy* FindPlayerEcon(); // Finds the player economy
	void SetResourceManager(ResourceManager* resourceManager);
	

	static PlayerEconManager* Create(GameObject *gameObject);
	void Copy(GameObject *copyObject);

	void OnLoad();
	void Update();
	void Start();


private:
	
	PlayerEconomy economyList[3]; // List of economies
	ResourceManager* resourceManager;
	PlayerEconomy playerEconomy;

};