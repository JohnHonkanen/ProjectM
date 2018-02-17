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
	int generatedResID = (rand() % 2) + 1; // Rand value should be between 1 and active resource in resource list. (Currently: 2)
	int generatedContractID = (rand() % 640000) + 1;

	Resources resource = resourceManager->FindResource(generatedResID);
	Contract contract = Contract(resource);

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

	printf("Contract ID: %i \n", contract.GetContractID());
	printf("Contract Issue Number: %i \n", contract.GetContractIndex()); // Edited. check
	printf("Resource name to deliver: %s \n", contract.GetResource().GetName().c_str());
	printf("Resource amount to deliver: %i \n", contract.GetAmount());
	printf("Currently fulfilled %i \n", contract.GetCurrent());
	printf("Contract Length: %i \n", contract.GetTime());
	printf("Contract Difficulty: %i \n", contract.GetDifficulty());
	printf("Contract Status: %i \n", contract.GetStatus());
	printf("Contract Complete: %i \n", contract.IsComplete());
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
	if (clock.Alarm()) {
		for (int i = 0; i < ResourceManager::sizeOfList; i++) {
			if(FindContract(i).GetStatus() == true) {
					if (contractList[i].GetTime() > 0) {
						contractList[i].ReduceTime();
						printf("Contract ID: %i \n", contractList[i].GetContractID());
						printf("Contract Issue Number: %i \n", contractList[i].GetContractIndex());
						printf("Contract Length: %i \n", contractList[i].GetTime());
						cout << endl;
						break;
					}
					else {
						FindContract(i).SetStatus(false);
						FindContract(i).IsComplete();
					}
			}
			else {
				if (FindContract(i).GetStatus() == false) {
					i = 0;
				}
			}
		}
		clock.ResetClock();
	}

	int addContractKey = Engine::GameEngine::manager.inputManager.GetKey("AddContract");

	if (addContractKey == 1) {
		if (keyReleased == true) {
			keyReleased = false;
			AddContract();
		}	
	}
	else {
		if (addContractKey == 0 ) {
			keyReleased = true;
		}
	}
}

void ContractManager::Start()
{
	Engine::GameEngine::manager.inputManager.AddKey("AddContract", "p");
	clock.SetDelay(1000);
	clock.StartClock();
	AddContract();
}
