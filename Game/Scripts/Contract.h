#pragma once

#include "components\Behaviour.h"
#include "core\GameObject.h"
#include "ResourceManager.h"

class Contract : public Behaviour{
public:
	Contract();
	Contract(Resources resource, int contractID, int paymentToRecieve, int amountToFulfill, int contractTime, int currentFulFilled, int difficultyLevel);
	~Contract();

	int GetDifficulty(); // Gets contract difficulty
	void SetDifficulty(); // Sets contract difficulty, default is 1.
	int GetPayment(); // Get payment amount player is to receive if contract is fulfilled.
	Resources GetResource(); 
	int GetAmount(); // Get amount to fulfill on contract
	void SetTime(); // Set time left on contract
	int GetTime(); // Get time left on contract
	int GetCurrent(); // Get current amount fulfilled of contract
	void SetContractID(int contractID); // Set contract ID

	void GenerateContract(); // generate contract
	void AddContract(int contractID); // Add contract to contract list
	bool GetStatus(); // Get the status of contract (true/false)
	void SetStatus(bool active); // Return true
	
	bool IsComplete(); // Return true

	static Contract* Create(GameObject *gameObject);
	void Copy(GameObject *copyObject);
	void Update();
	void Start();

	void DebugContractOnce(); // Use to debug contract

private:
	int payment, amount, time;
	int current = 0;
	int difficulty = 1;
	int contractID;
	Resources resource;
	ResourceManager resourceManager;

	bool active = false;
	bool complete = false;

	int ContractList[64]; // List of contracts to be held, and chosen from. parameter of contracts to be generated using rand() WIP.
};