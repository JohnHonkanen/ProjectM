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

void Contract::SetPayment(int paymentAmount)
{
	this->payment = paymentAmount;
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

int Contract::GetContractID()
{
	return this->contractID;
}

void Contract::SetContractID(int contractID)
{
	this->contractID = contractID;

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

void Contract::DebugContractOnce()
{
	// print result of contracts

	printf("Contract ID: %i\n", contractID);
}
