#include "Contract.h"
#include "ContractManager.h"

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

int Contract::GetAmount()
{
	return this->amount;
}

void Contract::SetAmount()
{
	tempDif = GetDifficulty();

	if (tempDif == 1) {
		this->amount = (rand() % 100) + 150;
	}
	else if (tempDif == 2) {
		this->amount = (rand() % 200) + 300;
	}
	else {
		this->amount = (rand() % 600) + 900;
	}
}

void Contract::SetTime(int timer)
{
	tempDif = GetDifficulty();

	if (tempDif == 1) {
		this->time = (rand() % 1000) + timer;
	}
	else if (tempDif == 2) {
		this->time = (rand() % 2000) + timer;
	}
	else {
		this->time = (rand() % 6000) + timer;
	}
}

int Contract::GetTime()
{
	return this->time;
}

int Contract::ReduceTime()
{
	this->time -= 1000;
	return this->time;
}


int Contract::GetCurrent()
{
	// currently fulfilled
	return this->current;
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
	return this->complete;
	cout << "Contract completed!" << endl << endl;
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
