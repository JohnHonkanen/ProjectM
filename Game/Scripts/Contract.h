#pragma once

#include "ResourceManager.h"
#include <string>

enum class ContractName {
	Player_Contract
};


class ContractManager;
class Contract{
public:
	Contract();
	Contract(ContractName contractName, Resources resource, ContractManager* contractManager, string nameOfContract);
	Contract(const Contract &copy);
	~Contract();

	int GetDifficulty(); // Gets contract difficulty
	void SetDifficulty(); // Sets random contract difficulty between 1 and 3. 
	int GetPayment(); // Get payment amount player is to receive if contract is fulfilled.
	void SetPayment(); // Set contract payment

	int GetContractBonus(); // Get bonus payment for contract

	Resources GetResource(); // Get resource in contract
	string GetResourceIcon(); // Get resource icon in contract
	int GetAmount(); // Get amount to fulfill on contract
	void SetAmount(); // Set amount of resource to fulfill on contract

	void SetTime(int timer); // Set time left on contract
	int GetTime(); // Get time left on contract
	int ReduceTime(int millisecond); // Reduce Time on contract over time.
	void StartTime(); // Sets this->begin to true. Use to start reduceTime() for contract.

	int GetCurrent(); // Get current amount fulfilled of contract
	int SetCurrent(int currentAmount); // Set current amount
	int IncreaseCurrent(int amountToIncrease); // Increase current amount fulfilled of contract
	int DecreaseCurrent(int amountToDecrease); // Decrease current amount fulfilled of contract

	int GetContractIndex(); // Get Contract Index
	int SetContractIndex(int contractIndex); // Set Contract index

	int GetContractID(); // Get Contract ID
	void SetContractID(int contractID); // Set contract ID

	bool GetStatus(); // Get the status of contract (true/false)
	void SetStatus(bool active); // Return true
	
	bool IsComplete(); // Return true
	bool InitComplete(bool completeStatus); // Initial complete, return false;

	int DifficultyModifier(int tempDif); // Calcualate bonus payment for contracts

	int GetResourceID(); // Resource ID for contract

	bool GetTaken() const;
	void SetTaken(bool taken);

private:
	int payment, tempDif, amount, contractBonus;
	int time = 120; 
	int current = 0;
	int difficulty = 1;
	int contractID, contractIndex, resourceID;
	int difficultyModifier = 100; // bonus

	bool begin = false;
	bool taken;
	Resources resource;
	ResourceManager* resourceManager;
	ContractManager* contractManager;
	ContractName contractName;

	bool active = false;
	bool complete = false;

	string nameOfContract;
};