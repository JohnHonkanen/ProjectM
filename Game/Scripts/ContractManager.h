#pragma once
#include "Contract.h"
#include "ResourceManager.h"
#include "PlayerEconManager.h"
#include "core\GameObject.h"
#include "utility\Clock.h"
#include <list>


class ContractManager {
public:
	ContractManager();
	~ContractManager();


	Contract AddContract();
	Contract FindContract(int contractID);
	Contract* FindPersistentContract(int contractID);
	Contract* FindContractQueueFront();
	Contract* FindContractQueueBack();
	int NumberOfActiveContract(); // Counts number of current active contract

	void SetManager(ResourceManager* resourceManager);
	void SetManager(PlayerEconManager* playerEconManager);
	void Update();
	void Start();

	list <Contract*> GetList() const;
	Contract * GetFirstAvailable() const;
private:
	int contractIndex = 0;
	
	Contract contractList[1064]; // List of contracts to be held, and chosen from. 
	ResourceManager* resourceManager;
	PlayerEconManager* playerEconManager;
	Engine::Utility::Clock clock;
	bool keyReleased1 = true;
	bool keyReleased2 = true;
	bool active, complete;
	bool statusCheck = true;

	list <Contract*> contractQueue; // Creates an empty queue of contractQueue 
};