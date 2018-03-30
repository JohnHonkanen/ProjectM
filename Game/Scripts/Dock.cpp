#include "Dock.h"
#include "components\MeshRenderer.h"

using namespace v1::TaskSystem;

Dock * Dock::Create()
{
	Dock *d = new Dock();
	d->name = "Dock";
	d->structureType = DOCK;
	d->type = "Dock";
	d->contractManager = &GameManager::gameManager->contractManager;
	d->tileWidth = 5;

	return d;
}

void Dock::Copy(GameObject * copyObject)
{
	copyObject->AddComponent(Create());
}

void Dock::Update()
{
	if (contract == nullptr)
	{
		//Scan for Contract
		return;
	}
}
