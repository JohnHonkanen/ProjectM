#include "ContractManager.h"

ContractManager::ContractManager()
{
}

ContractManager::~ContractManager()
{
}

Contract ContractManager::AddContract(Resources resourceID, int contractID, int paymentToRecieve, int amountToFulfill, int contractTime, int currentFulFilled, int difficultyLevel)
{
	int generatedResID = rand() % 64;
	//this->resource = resourceManager.FindResource(generatedResID);
	resourceID = resourceManager.FindResource(generatedResID);

	if (contractIndex >= ResourceManager::sizeOfList) {
		contractIndex = 0;
	}
	else {
		contractIndex++;
	}

	this->contractIndex = contractID;

	this->contract = Contract(resourceID, contractID, paymentToRecieve, amountToFulfill, contractTime, currentFulFilled, difficultyLevel);
	this->contractList[contractIndex] = contract;

	
	return this->contractList[contractIndex];
}

Contract ContractManager::FindContract()
{
	return Contract();
}

ContractManager * ContractManager::Create(GameObject * gameObject)
{
	ContractManager * c = new ContractManager();
	gameObject->AddComponent(c);
	return c;
}

void ContractManager::Copy(GameObject * copyObject)
{
}

void ContractManager::Update()
{
}

void ContractManager::Start()
{
}
