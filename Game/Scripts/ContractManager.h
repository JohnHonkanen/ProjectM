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
	ContractManager();
	~ContractManager();


	//Contract AddContract();
	Contract AddContract(ContractName contractName, string nameOfContract, int contractIndex);
	//Contract FindContract(int contractID);
	//Contract* FindPersistentContract(int contractID);
	//Contract* FindContractQueueFront();
	//Contract* FindContractQueueBack();
	int NumberOfActiveContract(); // Counts number of current active contract

	void SetManager(ResourceManager* resourceManager);
	void SetManager(PlayerEconManager* playerEconManager);
	void Update();
	void Start();

	//list <Contract*> GetList() const;
	Contract &GetFirstAvailable();

	ContractName GetContractName(); // Returns name of Contract from contractName enum
	int GetSizeOfListOfContract(); // Returns the size of listOfContract
	int GetIndexOfLastElement(int offSet); // Gets index ID for contract at last element of listOfContract + offSet
	Resources GenerateRandomResourceID();
	Contract &FindContract(ContractName contractName, int contractIndex);

	vector<Contract*> GetList() const; // Returns a listOfContract
	

private:
	int contractIndex = 3;
	
	//Contract contractList[1064]; // List of contracts to be held, and chosen from. 
	ResourceManager* resourceManager;
	PlayerEconManager* playerEconManager;
	Contract contract;
	Engine::Utility::Clock clock;
	bool keyReleased1 = true;
	bool keyReleased2 = true;
	bool active, complete;
	bool statusCheck = true;
	int contractNumber = 3;

	//list <Contract*> contractQueue; // Creates an empty queue of contractQueue 
	vector <Contract> listOfContract; // Creates a vector of list of contracts
	vector <vector<Contract>::iterator> listOfContractToDestroy; // Create a vector of list of contracts to destroy.
	ContractName contractName;
};