#pragma once
#include "Contract.h"
#include "ResourceManager.h"
#include "PlayerEconManager.h"
#include "core\GameObject.h"
#include "utility\Clock.h"
#include <list>
#include <vector>

#define PLAYER 0


class ContractManager {
public:
	ContractManager(); // Constructor
	~ContractManager(); // De-constructor

	Contract AddContract(ContractName contractName, string nameOfContract, int contractIndex); // Add a contract

	int NumberOfActiveContract(); // Counts number of current active contract

	void SetManager(ResourceManager* resourceManager); // Set the resourceManager
	void SetManager(PlayerEconManager* playerEconManager); // Set the PlayerEconManager
	void Update(); // Update loop
	void Start(); // Methods called on Start

	int GetFirstAvailable(); // Returns first available contract

	ContractName GetContractName(); // Returns name of Contract from contractName enum
	int GetSizeOfListOfContract(); // Returns the size of listOfContract
	int GetIndexOfLastElement(int offSet); // Gets index ID for contract at last element of listOfContract + offSet
	Resources GenerateRandomResourceID(); // Generate a random resource ID between 2 and max resourceList size.
	Contract &FindContract(ContractName contractName, int contractIndex); // Find a contract

	Contract GetContract(int index); // Gets a contract
	void StartContract(int index); // Starts a contract
	void CompleteContract(int index); // Completes a contract
	void IncreaseContractCurrent(int index, int amount); // Increase current amount fulfilled
	void RemoveContract(int index); // remove contract
	vector <Contract> GetList(); // Returns a vector of contracts
private:
	int contractIndex = 0;
	ResourceManager* resourceManager;
	PlayerEconManager* playerEconManager;
	Contract contract;
	Engine::Utility::Clock clock;
	bool keyReleased1 = true;
	bool keyReleased2 = true;
	bool active, complete;
	bool statusCheck = true;

	vector <Contract> listOfContract; // Creates a vector of list of contracts
	ContractName contractName;
};