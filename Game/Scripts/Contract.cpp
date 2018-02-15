#include "Contract.h"

Contract::Contract()
{
}

Contract::Contract(Resources resource, int paymentToRecieve, int amountToFulfill, int contractTime, int currentFullFilled)
{
	this->Resource = resource;
	this->payment = paymentToRecieve;
	this->amount = amountToFulfill;
	this->time = contractTime;
	this->current = currentFullFilled;
}

Contract::~Contract()
{
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
