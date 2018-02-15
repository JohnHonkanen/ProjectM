#include "Contract.h"

Contract::Contract()
{
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
