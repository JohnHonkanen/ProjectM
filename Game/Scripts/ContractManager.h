#pragma once
#include "Contract.h"
#include "ResourceManager.h"
#include "PlayerEconomy.h"
#include "components\Behaviour.h"
#include "core\GameObject.h"
#include "utility\Clock.h"

class ContractManager : public Behaviour {
public:
	ContractManager();
	~ContractManager();


	Contract AddContract();
	Contract FindContract(int contractID);

	static ContractManager* Create(GameObject *gameObject, ResourceManager* resourceManager);
	void Copy(GameObject *copyObject);
	void Update();
	void Start();

private:
	int contractIndex = 0;
	
	Contract contractList[ResourceManager::sizeOfList]; // List of contracts to be held, and chosen from. parameter of contracts to be generated using rand() WIP.
	ResourceManager* resourceManager;
	Engine::Utility::Clock clock;
	bool keyReleased = true;
	bool active, complete;
};