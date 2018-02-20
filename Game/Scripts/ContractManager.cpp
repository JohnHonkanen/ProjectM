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
	int numberOfResources = resourceManager->NumberOfActiveResources();
	int generatedResID = resourceManager->RandomResources(); 
	//cout << generatedResID << endl;
	int generatedContractID = (rand() % 640000) + 1;

	Resources resource = resourceManager->FindResource(generatedResID); // Add a random resource to contract
	Contract contract = Contract(resource, this);

	if (this->contractIndex >= ResourceManager::sizeOfList) {
		contractIndex = 0;
	}
	else {
		contractIndex++;
	}

	contract.SetContractID(generatedContractID);
	contract.SetDifficulty();
	contract.SetPayment();
	contract.SetTime(18000);
	contract.SetAmount();
	contract.SetContractIndex(contractIndex);
	contract.SetStatus(true);
	contract.InitComplete(false);

	this->contractList[contractIndex] = contract;

	//printf("Contract ID: %i \n", contract.GetContractID());
	//printf("Contract Issue Number: %i \n", contract.GetContractIndex()); 
	//printf("Resource name to deliver: %s \n", contract.GetResource().GetName().c_str());
	//printf("Resource amount to deliver: %i \n", contract.GetAmount());
	//printf("Currently fulfilled %i \n", contract.GetCurrent());
	//printf("Contract Length: %i \n", contract.GetTime());
	//printf("Contract Difficulty: %i \n", contract.GetDifficulty());
	//printf("Contract Status: %i \n", contract.GetStatus());
	//printf("Contract Complete: %i \n", contract.IsComplete());
	//cout << endl;

	return this->contractList[contractIndex];
}

Contract ContractManager::FindContract(int contractID)
{
	return this->contractList[contractID];
}

Contract * ContractManager::FindPersistentContract(int contractID)
{
	return &this->contractList[contractID];;
}

int ContractManager::NumberOfActiveContract()
{
	int count = 0;
	for (int i = 0; i < this->contractIndex; i++) {
		
		 count++;
	}
	return  count;
}


void ContractManager::SetResourceManager(ResourceManager* resourceManager)
{
	this->resourceManager = resourceManager;
}

void ContractManager::Update()
{
	clock.UpdateClock();

	if (clock.Alarm()) {

		for (int i = 0; i < NumberOfActiveContract(); i++) {
			FindPersistentContract(i+1)->ReduceTime(1000);
		}
		clock.ResetClock();
	}

	int addContractKey = Engine::GameEngine::manager.inputManager.GetKey("Add Contract");
	int changeCurrent = Engine::GameEngine::manager.inputManager.GetKey("Change Current");

	int counter = 0;
	// Add Contract
	if (addContractKey == 1) {
		if (keyReleased1 == true) {
			AddContract();
			cout << "Contract Added!" << endl;
			keyReleased1 = false;
			}
	}
	else {
		if (addContractKey == 0 ) {
			keyReleased1 = true;
			
		}
	}

	// Change current amount

	if (changeCurrent == 1) {
		if (keyReleased2 == true) { // if key j is pressed (Increase)
			keyReleased2 = false;
			FindPersistentContract(1)->IncreaseCurrent(5);
		}
	}
	else {
		if (changeCurrent == 0) {
			keyReleased2 = true;
		}
	}

	if (changeCurrent == -1) { 
		if (keyReleased2 == true) { // if key k is pressed (Decrease)
			keyReleased2 = false;
			FindPersistentContract(1)->DecreaseCurrent(5);
		}
	}
	else {
		if (changeCurrent == 0) {
			keyReleased2 = true;
		}
	}
}

void ContractManager::Start()
{
	Engine::GameEngine::manager.inputManager.AddKey("Add Contract", "p");
	GameEngine::manager.inputManager.AddKey("Change Current", "j", "k");
	clock.SetDelay(1000);
	clock.StartClock();
	AddContract();
	AddContract();
	AddContract();
}
