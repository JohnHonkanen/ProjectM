#pragma once
#include "Contract.h"
#include "ResourceManager.h"
#include "PlayerEconomy.h"
#include "core\GameObject.h"
#include "utility\Clock.h"

class ContractManager {
public:
	ContractManager();
	~ContractManager();


	Contract AddContract();
	Contract FindContract(int contractID);
	Contract* FindPersistentContract(int contractID);
	int NumberOfActiveContract(); // Counts number of current active contract

	void SetResourceManager(ResourceManager* resourceManager);
	void Update();
	void Start();

private:
	int contractIndex = 0;
	
	Contract contractList[ResourceManager::sizeOfList]; // List of contracts to be held, and chosen from. parameter of contracts to be generated using rand() WIP.
	ResourceManager* resourceManager;
	Engine::Utility::Clock clock;
	bool keyReleased1 = true;
	bool keyReleased2 = true;
	bool active, complete;
	bool statusCheck = true;
};