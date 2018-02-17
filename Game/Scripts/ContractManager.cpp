#include "ContractManager.h"
#include "core\GameEngine.h"
#include "core\InputManager.h"

ContractManager::ContractManager()
{
}

ContractManager::~ContractManager()
{
}

Contract ContractManager::AddContract()
{
	int generatedResID = 1; //rand() % 64;
	this->resource = resourceManager->FindResource(generatedResID);
	resource = this->resource;
	this->contractID = (rand() % 640000) + 1;

	contract.SetDifficulty();
	contract.SetPayment(100);
	contract.SetTime(180);
	contract.SetAmount();

	this->paymentAmount = contract.GetPayment();
	this->amountToFulfill = contract.GetAmount();
	this->currentlyFulFilled = 0;
	this->difficulty = contract.GetDifficulty();
	this->time = contract.GetTime();
	if (contractIndex >= ResourceManager::sizeOfList) {
		contractIndex = 0;
	}
	else {
		contractIndex++;
	}
	
	this->contract = Contract(resource, this->contractID, this->paymentAmount, this->amountToFulfill, this->time, this->currentlyFulFilled, this->difficulty);
	this->contractList[contractIndex] = contract;

	printf("Contract ID: %i \n", contract.GetContractID());
	//printf("Contract Issue Number: %i \n", contractIndex);
	printf("Resource name to deliver: %s \n", resource.GetName().c_str());
	printf("Resource amount to deliver: %i \n", contract.GetAmount());
	printf("Currently fulfilled %i \n", contract.GetCurrent());
	printf("Contract Length: %i \n", contract.GetTime());
	printf("Contract Difficulty: %i \n", contract.GetDifficulty());
	cout << endl;

	return this->contractList[contractIndex];
}

Contract ContractManager::FindContract(int contractID)
{
	return this->contractList[contractID];
}

ContractManager * ContractManager::Create(GameObject * gameObject, ResourceManager* resourceManager)
{
	ContractManager * c = new ContractManager();
	c->resourceManager = resourceManager;
	gameObject->AddComponent(c);
	return c;
}

void ContractManager::Copy(GameObject * copyObject)
{
}

void ContractManager::Update()
{
	clock.UpdateClock();
	//if (clock.Alarm()) {
	//	AddContract();
	//	clock.ResetClock();
	//}

	int AddContractKey = Engine::GameEngine::manager.inputManager.GetKey("AddContract");

	if (AddContractKey == 1) {
		if (keyReleased == true) {
			keyReleased = false;
			AddContract();
		}	
	}
	else {
		if (AddContractKey == 0 ) {
			keyReleased = true;
		}
	}
}

void ContractManager::Start()
{
	Engine::GameEngine::manager.inputManager.AddKey("AddContract", "p");
	clock.SetDelay(1000);
	clock.StartClock();
}
