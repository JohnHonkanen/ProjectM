#pragma once

#include "ResourceManager.h"

class ContractManager;
class Contract{
public:
	Contract();
	Contract(Resources resource, ContractManager* contractManager);
	~Contract();

	int GetDifficulty(); // Gets contract difficulty
	void SetDifficulty(); // Sets random contract difficulty between 1 and 3. 
	int GetPayment(); // Get payment amount player is to receive if contract is fulfilled.
	void SetPayment(); // Set contract payment
	Resources GetResource(); // Get resource in contract
	int GetAmount(); // Get amount to fulfill on contract
	void SetAmount(); // Set amount to fulfill on contract

	void SetTime(int timer); // Set time left on contract
	int GetTime(); // Get time left on contract
	int ReduceTime(int millisecond); // Reduce Time on contract over time.

	int GetCurrent(); // Get current amount fulfilled of contract
	int SetCurrent(int currentAmount); // Set current amount
	int IncreaseCurrent(int amountToIncrease); // Increase current amount fulfilled of contract
	int DecreaseCurrent(int amountToDecrease); // Decrease current amount fulfilled of contract

	int GetContractIndex(); // Get Contract Index
	int SetContractIndex(int contractIndex); // Set Contract index

	int GetContractID(); // Get Contract ID
	void SetContractID(int contractID); // Set contract ID

	bool GetStatus(); // Get the status of contract (true/false)
	bool SetStatus(bool active); // Return true
	
	bool IsComplete(); // Return true
	bool InitComplete(bool completeStatus); // Initial complete, return false;

	void DebugContractOnce(); // Use to debug contract

	int DifficultyModifier(int tempDif);

	int GetResourceID(); // Resource ID for contract
private:
	int payment, tempDif, amount;
	int time = 120; 
	int current = 0;
	int difficulty = 1;
	int contractID, contractIndex, resourceID;
	int difficultyModifier = 100; // bonus
	Resources resource;
	ResourceManager* resourceManager;
	ContractManager* contractManager;

	bool active = false;
	bool complete = false;
};