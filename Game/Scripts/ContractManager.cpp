#include "ContractManager.h"

ContractManager::ContractManager()
{
}

ContractManager::~ContractManager()
{
}

Contract ContractManager::AddContract(int amountToFulfill, int contractTime, int currentFulFilled, int difficultyLevel)
{
	int generatedResID = 1; //rand() % 64;
	this->resource = resourceManager.FindResource(generatedResID);
	this->contractID = rand() % 640000;

	contract.SetPayment(100);
	this->paymentAmount = contract.GetPayment();
	amountToFulfill = 100;
	currentFulFilled = 0;
	difficultyLevel = contract.GetDifficulty();

	if (contractIndex >= ResourceManager::sizeOfList) {
		contractIndex = 0;
	}
	else {
		contractIndex++;
	}

	this->contractIndex = contractID;
	
	this->contract = Contract(this->resource, this->contractID, this->paymentAmount, amountToFulfill, contractTime, currentFulFilled, difficultyLevel);
	this->contractList[contractIndex] = contract;

	cout << "contractID: " << contractID << endl;

	cout << resource.GetName();

	return this->contractList[contractIndex];
}

Contract ContractManager::FindContract(int contractID)
{
	return this->contractList[contractID];
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
