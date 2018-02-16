#pragma once
#include "Contract.h"
#include "ResourceManager.h"
#include "components\Behaviour.h"
#include "core\GameObject.h"

class ContractManager : public Behaviour {
public:
	ContractManager();
	~ContractManager();


	Contract AddContract(int amountToFulfill, int contractTime, int currentFulFilled, int difficultyLevel);
	Contract FindContract(int contractID);

	static ContractManager* Create(GameObject *gameObject);
	void Copy(GameObject *copyObject);
	void Update();
	void Start();

private:
	int contractIndex = 0;
	int contractID, paymentAmount;
	Resources resource;
	Contract contract;
	Contract contractList[ResourceManager::sizeOfList]; // List of contracts to be held, and chosen from. parameter of contracts to be generated using rand() WIP.
	ResourceManager resourceManager;
};