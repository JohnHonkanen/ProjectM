#pragma once
#include "Contract.h"
#include "ResourceManager.h"
#include "components\Behaviour.h"
#include "core\GameObject.h"

class ContractManager : public Behaviour {
public:
	ContractManager();
	~ContractManager();

	Contract AddContract(Resources resourceID, int contractID, int paymentToRecieve, int amountToFulfill, int contractTime, int currentFulFilled, int difficultyLevel);
	Contract FindContract(int contractID);

	static ContractManager* Create(GameObject *gameObject);
	void Copy(GameObject *copyObject);
	void Update();
	void Start();

private:
	int contractIndex = 0;
	Resources resource;
	Contract contract;
	Contract contractList[ResourceManager::sizeOfList];
	ResourceManager resourceManager;
};