#include "Contract.h"
#include "ContractManager.h"
#include "glm\glm.hpp"
#include "GameManager.h"

Contract::Contract()
{
	this->difficulty = -1;
}

Contract::Contract(ContractName contractName, Resources resource, ContractManager* contractManager, string nameOfContract)
{
	this->contractName = contractName;
	this->resource = resource;
	this->contractManager = contractManager;
	this->nameOfContract = nameOfContract;
}

Contract::Contract(const Contract & copy)
{
	this->contractName = copy.contractName;
	this->resource = copy.resource;
	this->contractManager = copy.contractManager;
	this->nameOfContract = copy.nameOfContract;
	this->contractID = copy.contractID;
	this->difficulty = copy.difficulty;
	this->payment = copy.payment;
	this->time = copy.time;
	this->amount = copy.amount;
	this->contractIndex = copy.contractIndex;
	this->active = copy.active;
	this->current = copy.current;
	this->resourceID = copy.resourceID;
	this->tempDif = copy.tempDif;
	this->resourceManager = copy.resourceManager;
	this->resource = copy.resource;
	this->difficultyModifier = copy.difficultyModifier;
	this->taken = copy.taken;
	this->complete = copy.complete;
	this->contractBonus = copy.contractBonus;
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
	// Generate random amount of resources to fulfill
	SetAmount();

	// Calculate Price of contract total reward.
	this->payment = resource.GetBasePrice() * GetAmount() + GetContractBonus();
}

int Contract::GetContractBonus()
{
	return this->contractBonus = DifficultyModifier(GetDifficulty());
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
		this->amount = (rand() % 10);
	}
	else if (tempDif == 2) {
		this->amount = (rand() % 20);
	}
	else {
		this->amount = (rand() % 60);
	}
}

void Contract::SetTime(int timer)
{

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
	if (!begin) {
		return this->time;
	} 

	this->time -= millisecond;

	if (this->time < 0) {
		this->time = 0;
		SetStatus(false);
		IsComplete();
	}
	return this->time;
}

void Contract::StartTime()
{
	this->begin = true;
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
		// Calculate value of amount delivered + add to player economy + adjust contract current.
		int amountDelivered = GetResource().GetBasePrice() * amountToIncrease;
		GameManager::gameManager->playerEconManager.FindPlayerEcon(EconName::Player_Econ)->AddGoldBars(amountDelivered);
		
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
		// Calculate value of amount deducted + deduct from player economy + adjust contract current.
		int amountDelivered = GetResource().GetBasePrice() * amountToDecrease;
		GameManager::gameManager->playerEconManager.FindPlayerEcon(EconName::Player_Econ)->RemoveGoldBars(amountDelivered);
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

void Contract::SetStatus(bool active) 
{
	this->active = active;
}

bool Contract::IsComplete() 
{
	SetStatus(false); // Set contract status to false
	return this->complete = true;
}

bool Contract::InitComplete(bool completeStatus)
{
	this->complete = completeStatus;
	return this->complete;
}


int Contract::DifficultyModifier(int tempDif)
{
	return this->difficultyModifier * tempDif;;
}

int Contract::GetResourceID()
{
	return this->resourceID;
}

bool Contract::GetTaken() const
{
	return taken;
}

void Contract::SetTaken(bool in_taken)
{
	taken = in_taken;
}
