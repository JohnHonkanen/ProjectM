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
	this->difficulty = rand() % 3;
}

int Contract::GetPayment()
{
	return this->payment;
}

void Contract::SetPayment(int paymentAmount)
{
	tempDif = GetDifficulty();

	//TO:DO Take resource value into account when calculating payment amount to set + difficulty level as a modifier
	if (tempDif == 1) {
		this->payment = rand() % 10 + paymentAmount;
	}
	else if (tempDif == 2) {
		this->payment = rand() % 20 + paymentAmount;
	}
	else {
		this->payment = rand() % 60 + paymentAmount;
	}
}

Resources Contract::GetResource()
{
	return this->resource;
}

int Contract::GetAmount()
{
	return this->amount;
}

void Contract::SetAmount()
{
	tempDif = GetDifficulty();

	if (tempDif == 1) {
		this->amount = rand() % 100 + 150;
	}
	else if (tempDif == 2) {
		this->amount = rand() % 200 + 300;
	}
	else {
		this->amount = rand() % 600 + 900;
	}
}

void Contract::SetTime(int timer)
{
	this->time = timer;
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
