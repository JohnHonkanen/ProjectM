#include "Dock.h"
#include "components\MeshRenderer.h"
#include "TradeShipSpawner.h"
using namespace v1::TaskSystem;

Dock * Dock::Create()
{
	return Create(5, 150);
}

Dock * Dock::Create(int upkeep, int cost)
{
	Dock *d = new Dock();
	d->name = "Dock";
	d->structureType = DOCK;
	d->type = "Dock";
	d->contractManager = &GameManager::gameManager->contractManager;
	d->hub = GameManager::gameManager->GetHub();
	d->tileWidth = 5;
	d->contractFufilled = true;
	d->isActive = false;
	d->upkeep = upkeep;
	d->cost = cost;

	d->timer.StartClock();
	d->timer.SetDelay(1000);

	return d;
}

void Dock::Copy(GameObject * copyObject)
{
	copyObject->AddComponent(Create(upkeep, cost));
}

void Dock::Start()
{
}

void Dock::Update()
{
	if (!isActive)
	{
		return;
	}

 	if (contract == nullptr || contract->GetContractID() != contractID)
	{
		if (dockedShip != nullptr)
		{
			dockedShip->Return();
			dockedShip = nullptr;
			docked = false;
		}
		//Scan for Contract
		contract = &contractManager->GetFirstAvailable();

		if (contract->GetDifficulty() != -1)
		{
			inventory.Clear();
			task = Task();
			contractFufilled = true;
			GameManager::gameManager->GetTradeShipSpawner()->CreateTradeShip(this);
			contractID = contract->GetContractID();
		}
		else {
			contract = nullptr;
		}

		

		return;
	}

	//Found Contract, now do something
	if (task == TASK_TYPE::NONE && contractFufilled)
	{
		//Configure our task and send it on.
		task = Task(TASK_TYPE::REQUEST, 20, this, nullptr, contract->GetResource().GetResouceID(), contract->GetAmount());
		hub->GetTaskManager()->AddTask(task, task.GetPriority());

		contractFufilled = false;
	}

	if (dockedShip)
	{
		if (!contractFufilled)
		{
			int inInventory = inventory.Contains(contract->GetResource().GetResouceID());

			//Nothing to do
			if (inInventory == 0)
			{
				return;
			}

			int potential = contract->GetCurrent() + inInventory;


			contract->IncreaseCurrent(inInventory);
			inventory.Remove(contract->GetResource().GetResouceID(), inInventory);

			if (potential >= contract->GetAmount())
			{
				contractFufilled = true;
				contract = nullptr;

				task = Task();
				//Flush Inventory of Junk
				inventory.Clear();


				dockedShip->Return();
				dockedShip = nullptr;
				docked = false;
			}
		}
	}
	

}

void Dock::DockShip(TradeShip * ship)
{
	dockedShip = ship;
	docked = true;
}

vec3 Dock::ParkingLocation()
{
	return transform->GetPosition() + vec3(30, 0, 0);
}
