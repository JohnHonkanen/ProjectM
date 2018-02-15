#include "Contract.h"

Contract::Contract()
{
}

Contract::Contract(Resources resource, int paymentToRecieve, int amountToFulfill, int contractTime, int currentFulFilled, int difficultyLevel)
{
	this->Resource = resource;
	this->payment = paymentToRecieve;
	this->amount = amountToFulfill;
	this->time = contractTime;
	this->current = currentFulFilled;
	this->difficulty = difficultyLevel;
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
