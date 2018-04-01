#include "ContractManager.h"
#include "core\GameEngine.h"
#include "core\InputManager.h"

ContractManager::ContractManager()
{
}

ContractManager::~ContractManager()
{
}

//Contract ContractManager::AddContract()
//{
//	int generatedContractID = (rand() % 640000) + 1;
//
//	Contract contract = Contract(ContractName::Player_Contract, GenerateRandomResourceID(), this, "");
//
//	if (this->contractIndex >= ResourceManager::sizeOfList) {
//		contractIndex = 0;
//	}
//	else {
//		contractIndex++;
//	}
//
//	contract.SetContractID(generatedContractID);
//	contract.SetDifficulty();
//	contract.SetPayment();
//	contract.SetTime(1000000);
//	contract.SetAmount();
//	contract.SetContractIndex(contractIndex);
//	contract.SetStatus(true);
//	contract.InitComplete(false);
//
//	this->contractList[contractIndex] = contract;
//
//	this->contractQueue.push_back(&this->contractList[contractIndex]);
//
//	//cout << "New Contract added! : "  << contractQueue.back()->GetContractIndex() << endl;
//	return this->contractList[contractIndex];
//}

Contract ContractManager::AddContract(ContractName contractName, string nameOfContract, int contractIndex)
{
	Contract contract = Contract(contractName, GenerateRandomResourceID(), this, nameOfContract);

	switch (contractName) {
	case ContractName::Player_Contract:

		contract.SetContractID(contractIndex);
		contract.SetDifficulty();
		contract.SetPayment();
		contract.SetTime(1000000);
		contract.SetAmount();
		contract.SetContractIndex(contractIndex);
		contract.SetStatus(true);
		contract.InitComplete(false);

		this->listOfContract.push_back(contract);
		break;
	default:
		cout << "ERROR::NO_CONTRACT_NAME_FOUND::CANNOT_ADD_CONTRACT::" << endl;
		break;
	}
	return contract;
}
//
//Contract ContractManager::FindContract(int contractID)
//{
//	return this->contractList[contractID];
//}
//
//Contract * ContractManager::FindPersistentContract(int contractID)
//{
//	return &this->contractList[contractID];;
//}
//
//Contract * ContractManager::FindContractQueueFront()
//{
//	return this->contractQueue.front();
//}
//
//Contract * ContractManager::FindContractQueueBack()
//{
//	return  this->contractQueue.back();;
//}

int ContractManager::NumberOfActiveContract()
{

	if (!this->contractQueue.empty()) {
		return this->contractQueue.size();
	}
	else {
		AddContract(ContractName::Player_Contract, "", GetIndexOfLastElement(9));
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
		for (Contract* c : this->listOfContract) {
			if (c->GetTime() > 0 && c->GetStatus() == true) {
				c->ReduceTime(1000);
			}
		}
		clock.ResetClock();
	}
	
	// If contract status is no longer active (false), then pop from contractQueue + add a new contract.
	if (this->contractQueue.front()->GetStatus() == false) {
		AddContract(ContractName::Player_Contract, "", GetIndexOfLastElement(9));
		this->contractQueue.pop_front();
	}

	// Set contract status to iscomplete if timer reaches 0 
	if (this->contractQueue.front()->GetTime() <= 0) {
		this->contractQueue.front()->IsComplete();
	}

	// Complete contract when resource requirement is fulfilled.
	if (this->contractQueue.front()->GetCurrent() >= this->contractQueue.front()->GetAmount()) {
		
		PlayerEconomy* pEcon = playerEconManager->FindPlayerEcon(EconName::Player_Econ);
		pEcon->AddGoldBars(contractQueue.front()->GetPayment());

		this->contractQueue.front()->IsComplete();
	}

	int addContractKey = Engine::GameEngine::manager.inputManager.GetKey("Add Contract");
	int changeCurrent = Engine::GameEngine::manager.inputManager.GetKey("Change Current");

	int counter = 0;
	// Add Contract
	if (addContractKey == 1) {
		if (keyReleased1 == true) {
			AddContract(ContractName::Player_Contract, "", GetIndexOfLastElement(9));
			
			//cout << "Contract Added!" << endl;
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
			this->contractQueue.front()->IncreaseCurrent(5);
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
			this->contractQueue.front()->DecreaseCurrent(5);
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

	listOfContract.reserve(3);
	for (int i = 0; i < 3; i++) {
		AddContract(ContractName::Player_Contract, to_string(i), GetIndexOfLastElement(9));
	}
	
}

//list<Contract*> ContractManager::GetList() const
//{
//	return contractQueue;
//}

Contract * ContractManager::GetFirstAvailable() const
{
	bool completed = true;
	for (auto contract : listOfContract)
	{
		if (contract.IsComplete() == !completed) {
			if (!contract.GetTaken())
			{
				contract.SetTaken(true);
				return &contract;
			}
		}
		
	}

	if (completed) {
		cout << "ERROR::GETFIRSTAVAILABLE::CONTRACT::ISCOMPLETED" << endl;
		return &Contract();
	}
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

Contract *ContractManager::FindContract(ContractName contractName, int contractIndex)
{
	// Find contract based on number of trade depo
	switch (contractName) {
	case ContractName::Player_Contract:
			return &listOfContract[contractIndex];

	default:
		cout << "ERROR::COULD_NOT_FIND_CONTRACT:: " << endl;
		return nullptr;
	}
	
}

vector<Contract*> ContractManager::GetList() const
{
	return vector<Contract*>();
}
