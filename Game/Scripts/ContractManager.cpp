#include "ContractManager.h"
#include "core\GameEngine.h"
#include "core\InputManager.h"

ContractManager::ContractManager()
{
}

ContractManager::~ContractManager()
{
}

Contract ContractManager::AddContract(int amountToFulfill, int contractTime, int currentFulFilled, int difficultyLevel)
{
	int generatedResID = 1; //rand() % 64;
	this->resource = resourceManager->FindResource(generatedResID);
	resource = this->resource;
	this->contractID = (rand() % 640000) + 1;

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
	
	this->contract = Contract(resource, this->contractID, this->paymentAmount, amountToFulfill, contractTime, currentFulFilled, difficultyLevel);
	this->contractList[contractIndex] = contract;

	cout << "contractIndex: " << contractIndex << endl;
	cout << "contractID: " << contractID << endl;
	cout << "resource Name: " << resource.GetName() << endl << endl;

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
		AddContract(0, 0, 0, 0);
		cout << "Contract ID: " << contract.GetContractID() << " added!" << endl;
		clock.ResetClock();
	}

	int keyPressed = Engine::GameEngine::manager.inputManager.GetKey("AddContract");

	if (keyPressed == 1) {
		AddContract(0, 0, 0, 0);
		cout << "Contract ID: "  << contract.GetContractID() << " added!" << endl;
	}
	else {
		if (keyPressed == -1 || keyPressed == 0) {
			// make sure key only pressed once
		}
	}
}

void ContractManager::Start()
{
	Engine::GameEngine::manager.inputManager.AddKey("AddContract", "p");
	clock.SetDelay(1000);
	clock.StartClock();
}
