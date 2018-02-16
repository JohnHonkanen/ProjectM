#include "Contract.h"

Contract::Contract()
{
}

Contract::Contract(Resources resource, int contractID, int paymentToRecieve, int amountToFulfill, int contractTime, int currentFulFilled, int difficultyLevel)
{
	this->resource = resource;
	this->payment = paymentToRecieve;
	this->amount = amountToFulfill;
	this->time = contractTime;
	this->current = currentFulFilled;
	this->difficulty = difficultyLevel;
	this->contractID = contractID;
}

Contract::~Contract()
{
}

int Contract::GetDifficulty()
{
	return this->difficulty;
}

void Contract::SetDifficulty()
{
	this->difficulty = difficulty;
}

int Contract::GetPayment()
{
	return this->payment;
}

Resources Contract::GetResource()
{
	return this->resource;
}

int Contract::GetAmount()
{
	return this->amount;
}

void Contract::SetTime()
{
	this->time = time;
}

int Contract::GetTime()
{
	return this->time;
}


int Contract::GetCurrent()
{
	// currently fulfilled
	return this->current;
}

void Contract::SetContractID(int contractID)
{
	this->contractID = contractID;

}

void Contract::GenerateContract()
{
	int temp = rand() % 64;

	int itemID = 1;//rand() % 64 + 1; // Skip 0, 0 is gold.
	this->resource = resourceManager.FindResource(itemID);

	contractID = rand() % 640000 / 3 + 1;

	cout << "contractID: " << contractID << endl;

	cout << resource.GetName();

	//Contract(Resources resource, int contractID, int paymentToRecieve, int amountToFulfill, int contractTime, int currentFulFilled, int difficultyLevel);

}

void Contract::AddContract(int contractID)
{
}

bool Contract::GetStatus()
{
	return this->active;
}

void Contract::SetStatus(bool active)
{
	this->active = true;
}

bool Contract::IsComplete()
{
	return this->complete;
}

Contract * Contract::Create(GameObject * gameObject)
{
	Contract * c = new Contract();
	gameObject->AddComponent(c);
	return c;
}

void Contract::Copy(GameObject * copyObject)
{
}

void Contract::Update()
{
}

void Contract::Start()
{
}

void Contract::DebugContractOnce()
{
	// print result of contracts

	printf("Contract ID: %i\n", contractID);
}
