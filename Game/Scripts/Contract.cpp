#include "Contract.h"
#include "ContractManager.h"
#include "glm\glm.hpp"

Contract::Contract()
{
}

Contract::Contract(Resources resource, ContractManager* contractManager)
{
	this->resource = resource;
	this->contractManager = contractManager;
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
	this->difficulty = (rand() % 3) + 1;
}

int Contract::GetPayment()
{
	return this->payment;
}

void Contract::SetPayment()
{
	int tempDif = GetDifficulty();
	SetAmount();

	if (tempDif == 1) {
		this->payment = DifficultyModifier(tempDif) + (resource.GetBasePrice() * GetAmount());
	}
	else if (tempDif == 2) {
		this->payment = DifficultyModifier(tempDif) + (resource.GetBasePrice() * GetAmount());
	}
	else {
		this->payment = DifficultyModifier(tempDif) + (resource.GetBasePrice() * GetAmount());
	}
}

Resources Contract::GetResource()
{
	return this->resource;
}

string Contract::GetResourceIcon()
{
	return GetResource().GetResourceIcon();
}

int Contract::GetAmount()
{
	return this->amount;
}

void Contract::SetAmount()
{
	tempDif = GetDifficulty();

	if (tempDif == 1) {
		this->amount = (rand() % 10) + 15;
	}
	else if (tempDif == 2) {
		this->amount = (rand() % 20) + 30;
	}
	else {
		this->amount = (rand() % 60) + 90;
	}
}

void Contract::SetTime(int timer)
{

	//this->time = timer;

	tempDif = GetDifficulty();

	if (tempDif == 1) {
		this->time = (rand() % 5000) + timer;
	}
	else if (tempDif == 2) {
		this->time = (rand() % 10000) + timer;
	}
	else {
		this->time = (rand() % 40000) + timer;
	}
}

int Contract::GetTime()
{
	return this->time;
}

int Contract::ReduceTime(int millisecond)
{
	this->time -= millisecond;

	if (this->time < 0) {
		this->time = 0;
		SetStatus(false);
		IsComplete();
	}
	return this->time;
}


int Contract::GetCurrent()
{
	// currently fulfilled
	return this->current;
}

int Contract::SetCurrent(int currentAmount)
{
	return this->current = currentAmount;
}

int Contract::IncreaseCurrent(int amountToIncrease)
{
	if (GetCurrent() >= GetAmount()) {
		return SetCurrent(GetAmount());
	}
	else {
		this->current += amountToIncrease;
		return SetCurrent(this->current);
	}
}

int Contract::DecreaseCurrent(int amountToDecrease)
{
	if (GetCurrent() <= 0) {
		return SetCurrent(0);
	}
	else {
		this->current -= amountToDecrease;
		return SetCurrent(this->current);
	}
}

int Contract::GetContractIndex()
{
	return this->contractIndex;
}

int Contract::SetContractIndex(int contractIndex)
{
	return this->contractIndex = contractIndex;
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

bool Contract::SetStatus(bool active)
{
	return this->active = active;
}

bool Contract::IsComplete()
{
	SetStatus(false);
	//cout << "Contract: " <<  GetContractIndex() << " completed!" << endl << endl;
	return this->complete;
}

bool Contract::InitComplete(bool completeStatus)
{
	this->complete = completeStatus;
	return this->complete;
}

void Contract::DebugContractOnce()
{
	// print result of contracts

	printf("Contract ID: %i\n", contractID);
}

int Contract::DifficultyModifier(int tempDif)
{
	difficultyModifier = this->difficultyModifier * tempDif;

	return difficultyModifier;
}

int Contract::GetResourceID()
{
	return this->resourceID;
}
