#include "Contract.h"

Contract::Contract()
{
}

Contract::Contract(Resources resource, int contractID, int paymentToRecieve, int amountToFulfill, int contractTime, int currentFulFilled, int difficultyLevel)
{
	this->Resource = resource;
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
	return this->Resource;
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

void Contract::SetContractID()
{
	contractID = rand() % 5 + 1;
	this->contractID = contractID;

}

void Contract::GenerateContract()
{
	int itemID = Resource.GetItemID();
	this->Resource = itemID;
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

void Contract::DebugContract()
{
	// print result of contracts

	printf("Contract ID: %i\n", contractID);
}
