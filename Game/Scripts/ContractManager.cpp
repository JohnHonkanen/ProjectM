#include "ContractManager.h"
#include "core\GameEngine.h"
#include "core\InputManager.h"
#include "GameManager.h"

ContractManager::ContractManager()
{
}

ContractManager::~ContractManager()
{
}


Contract ContractManager::AddContract(ContractName contractName, string nameOfContract, int contractIndex)
{
	Contract contract = Contract(contractName, GenerateRandomResourceID(), this, nameOfContract);

	switch (contractName) {
	case ContractName::Player_Contract:
		
		contract.SetContractID(contractIndex);
		contract.SetDifficulty();
		contract.SetPayment();
		contract.SetTime(1000000);
		contract.SetContractIndex(contractIndex);
		contract.SetStatus(true);
		contract.InitComplete(false);

		this->listOfContract.push_back(contract);

		return contract;
		break;
	default:
		cout << "ERROR::NO_CONTRACT_NAME_FOUND::CANNOT_ADD_CONTRACT::" << endl;
		break;
	}
	return this->contract;
}

int ContractManager::NumberOfActiveContract()
{

	if (!this->listOfContract.empty()) {
		return this->listOfContract.size();
	}
	else {
		AddContract(ContractName::Player_Contract, "", GetIndexOfLastElement(0));
	}
}


void ContractManager::SetManager(ResourceManager* resourceManager)
{
	this->resourceManager = resourceManager;
}

void ContractManager::SetManager(PlayerEconManager * playerEconManager)
{
	this->playerEconManager = playerEconManager;
}


void ContractManager::Update()
{
	clock.UpdateClock();

	if (clock.Alarm()) {
		listOfContract.reserve(this->listOfContract.size());
		for (Contract &c : this->listOfContract) {
			if (c.GetTime() > 0 && c.GetStatus() == true) {
				c.ReduceTime(1000);
			}
		}
		clock.ResetClock();
	}
	
	//GameManager::gameManager->GetHub()->GetNumberOf(StructureType::DOCK);

	// If new dock is detected, add new contract.
	if (this->listOfContract.size() < GameManager::gameManager->GetHub()->GetNumberOf(StructureType::DOCK)) {
		this->contractIndex++;
		AddContract(ContractName::Player_Contract, to_string(this->contractIndex), this->contractIndex);
		
		cout << listOfContract.size() << endl;
	}

	// Loop through listOfContract to determine if contract needs to be set as isComplete().
	for (int i = 0; i < this->listOfContract.size();) {

		// Set contract status to isComplete if timer reaches 0 
		if (this->listOfContract[i].GetTime() <= 0) {
			this->listOfContract[i].IsComplete();
		}


		i++;
	}

	int addContractKey = Engine::GameEngine::manager.inputManager.GetKey("Add Contract");
	int changeCurrent = Engine::GameEngine::manager.inputManager.GetKey("Change Current");

	int counter = 0;
	// Add Contract
	if (addContractKey == 1) {
		if (keyReleased1 == true) {
			AddContract(ContractName::Player_Contract, "", GetIndexOfLastElement(9));
			
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

			this->listOfContract.front().IncreaseCurrent(5);
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
			this->listOfContract.front().DecreaseCurrent(5);
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
}

int ContractManager::GetFirstAvailable()
{
	for (int i = 0; i < listOfContract.size(); i++)
	{
		if (!listOfContract[i].GetTaken())
		{
			listOfContract[i].SetTaken(true);
			return i;
		}
	}

	return -1;

}

ContractName ContractManager::GetContractName()
{
	return this->contractName;
}

int ContractManager::GetSizeOfListOfContract()
{
	return listOfContract.size();
}

int ContractManager::GetIndexOfLastElement(int offSet)
{
	return listOfContract.size() + offSet;
}

Resources ContractManager::GenerateRandomResourceID()
{
	int generatedResID = 3; //resourceManager->RandomResources(); 
	Resources resource = resourceManager->FindResource(generatedResID);
	return resource;
}

Contract &ContractManager::FindContract(ContractName contractName, int contractIndex)
{
	// Find contract based on number of trade depo
	switch (contractName) {
	case ContractName::Player_Contract:
		return this->listOfContract[contractIndex];

	default:
		cout << "ERROR::COULD_NOT_FIND_CONTRACT:: " << endl;
		break;
	}
	
}

Contract ContractManager::GetContract(int index)
{
	return listOfContract[index];
}

void ContractManager::StartContract(int index)
{
	listOfContract[index].StartTime();
}

void ContractManager::CompleteContract(int index)
{
	listOfContract[index].IsComplete();
}

void ContractManager::IncreaseContractCurrent(int index, int amount)
{
	listOfContract[index].IncreaseCurrent(amount);
}

void ContractManager::RemoveContract(int index)
{
	listOfContract.erase(listOfContract.begin() + index);
	AddContract(ContractName::Player_Contract, to_string(this->contractIndex), this->contractIndex);
	this->contractIndex++;
}

vector<Contract> ContractManager::GetList()
{
	return listOfContract;
}
