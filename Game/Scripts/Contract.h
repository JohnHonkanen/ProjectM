#pragma once

#include "ResourceManager.h"

class Contract{
public:
	Contract();
	Contract(Resources resourceID, int contractID, int paymentToRecieve, int amountToFulfill, int contractTime, int currentFulFilled, int difficultyLevel, bool activeStatus, bool complete, int contractIndex);
	~Contract();

	int GetDifficulty(); // Gets contract difficulty
	void SetDifficulty(); // Sets random contract difficulty between 1 and 3. 
	int GetPayment(); // Get payment amount player is to receive if contract is fulfilled.
	void SetPayment(int paymentAmount); // Set contract payment
	Resources GetResource(); 
	int GetAmount(); // Get amount to fulfill on contract
	void SetAmount(); // Set amount to fulfill on contract

	void SetTime(int timer); // Set time left on contract
	int GetTime(); // Get time left on contract
	int ReduceTime(); // Reduce Time on contract over time.

	int GetCurrent(); // Get current amount fulfilled of contract

	int GetContractIndex(); // Get Contract Index
	int SetContractIndex(int contractIndex); // Set Contract index

	int GetContractID(); // Get Contract ID
	void SetContractID(int contractID); // Set contract ID

	bool GetStatus(); // Get the status of contract (true/false)
	bool SetStatus(bool active); // Return true
	
	bool IsComplete(); // Return true
	bool InitComplete(bool completeStatus); // Initial complete, return false;

	void DebugContractOnce(); // Use to debug contract

private:
	int payment, amount, tempDif;
	int time = 120; 
	int current = 0;
	int difficulty = 1;
	int contractID, contractIndex;
	Resources resource;
	ResourceManager resourceManager;

	bool active = false;
	bool complete = false;
};