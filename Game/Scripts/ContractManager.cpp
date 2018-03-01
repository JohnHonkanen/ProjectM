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

	this->contractQueue.push(this->contractList[contractIndex]);

	cout << "New Contract added! : "  << contractQueue.back().GetContractIndex() << endl;
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

	if (!this->contractQueue.empty()) {
		return this->contractQueue.size();
	}
	else {
		AddContract();
	}
}


void ContractManager::SetResourceManager(ResourceManager* resourceManager)
{
	this->resourceManager = resourceManager;
}

void ContractManager::Update()
{
	clock.UpdateClock();

	if (clock.Alarm()) {

		for (int i = 0; i <= NumberOfActiveContract(); i++) {

				// Reduce contract time if greater than 0
				if (FindPersistentContract(i + 1)->GetTime() > 0 && FindPersistentContract(i+1)->GetStatus() == true) {
					FindPersistentContract(i + 1)->ReduceTime(1000);
				}
			}
		}

		// If contract status is no longer active (false), then pop from contractQueue + add a new contract.
		if (this->contractQueue.front().GetStatus() == false) {
			this->contractQueue.pop();
			AddContract();
		}

		// Set contract status to iscomplete if timer reaches 0 
		if (this->contractQueue.front().GetTime() <= 0) {
			this->contractQueue.front().IsComplete();
			
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
