#pragma once

#include "ResourceManager.h"

class Contract{
public:
	Contract();
	Contract(Resources resourceID, int contractID, int paymentToRecieve, int amountToFulfill, int contractTime, int currentFulFilled, int difficultyLevel);
	~Contract();

	int GetDifficulty(); // Gets contract difficulty
	void SetDifficulty(); // Sets contract difficulty, default is 1.
	int GetPayment(); // Get payment amount player is to receive if contract is fulfilled.
	void SetPayment(int paymentAmount); // Set contract payment
	Resources GetResource(); 
	int GetAmount(); // Get amount to fulfill on contract
	void SetTime(); // Set time left on contract
	int GetTime(); // Get time left on contract
	int GetCurrent(); // Get current amount fulfilled of contract
	int GetContractID(); // Get Contract ID
	void SetContractID(int contractID); // Set contract ID

	bool GetStatus(); // Get the status of contract (true/false)
	void SetStatus(bool active); // Return true
	
	bool IsComplete(); // Return true

	void DebugContractOnce(); // Use to debug contract

private:
	int payment, amount;
	int time = 120; 
	int current = 0;
	int difficulty = 1;
	int contractID;
	Resources resource;
	ResourceManager resourceManager;

	bool active = false;
	bool complete = false;
};