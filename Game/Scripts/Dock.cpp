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

Dock * Dock::Create(int upkeep, int cost, DockName dockName, string nameOfDock)
{
	Dock *d = new Dock();
	d->name = nameOfDock;
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
	AddToMarketDump(ResourceName::Chicken, 100);
	AddToMarketRequest(ResourceName::Chicken, 100);
}

void Dock::Update()
{
	if (!isActive)
	{
		return;
	}

	MarketDumpTaskee();
	BufferMarket();

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

	switch (dockName) {
	case DockName::Contract: // Currently, a general dock for everything
		GenerateContractConfiguration();
		break;
	case DockName::Local_Market:
		GenerateLocalMarketConfiguration();
		break;
	case DockName::Galactic_Market:
		GenerateGalacticMarketConfiguration();
		break;

	default:
		cout << "ERROR::NO_VALID_CONFIGURATION::" << endl;
		break;
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

void Dock::GenerateContractConfiguration()
{

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

void Dock::GenerateLocalMarketConfiguration()
{

}

void Dock::GenerateGalacticMarketConfiguration()
{
}

void Dock::AddToMarketDump(ResourceName resourceName, int amountToDump)
{
	marketDump.AddItem(resourceName, amountToDump);
}

void Dock::AddToMarketRequest(ResourceName resourceName, int amountToRequest)
{
	marketRequest.AddItem(resourceName, amountToRequest);
}

void Dock::TaskCompleted(TASK_TYPE type, int index)
{
	if (type == TASK_TYPE::COLLECT) {
		marketTask = v1::TaskSystem::Task();
	}
	else {
		if (index == 0) {
			task = v1::TaskSystem::Task();
		}
		else if(index == 1){
			marketRequestTask = v1::TaskSystem::Task();
		}
	}
}

int Dock::Collect(ResourceName resourceName, int resourceAmount, int index)
{
	int toRemove = resourceAmount;
	int contains = marketDump.Contains(resourceName);
	if (contains < resourceAmount)
	{
		toRemove = contains;
	}

	marketDump.Remove(resourceName, toRemove);

	return toRemove;

}

int Dock::Deposit(ResourceName resourceName, int resourceAmount, int index)
{
	if (index == 0) {
		inventory.AddItem(resourceName, resourceAmount);
	}
	else if (index == 1) {
		marketPlaceBuffer.AddItem(resourceName, resourceAmount);
	}
	
	return 0;
}

void Dock::MarketDumpTaskee()
{

	//Found Contract, now do something
	if (marketTask == TASK_TYPE::NONE)
	{
		auto resources = marketDump.Contains();
		if (!resources.empty()) {
			//Configure our task and send it on.
			marketTask = Task(TASK_TYPE::COLLECT, 50, this, this, resources[0].resource, 0);
			hub->GetTaskManager()->AddTask(marketTask, marketTask.GetPriority());

			}
		}

	//Found Contract, now do something
	if (marketRequestTask == TASK_TYPE::NONE)
	{
		auto resources = marketRequest.Contains();
		if (!resources.empty()) {
			//Configure our task and send it on.
			marketRequestTask = Task(TASK_TYPE::REQUEST, 100, this, nullptr, resources[0].resource, resources[0].quantity, 1);
			hub->GetTaskManager()->AddTask(marketRequestTask, marketRequestTask.GetPriority());

		}
	}
}

void Dock::BufferMarket()
{
	auto bufferResources = marketPlaceBuffer.Contains();

	while (!bufferResources.empty()) {
		ResourceName resource = bufferResources[0].resource;
		int quantity = bufferResources[0].quantity;
		int quantityNeeded = marketRequest.Contains(resource);

		if (quantityNeeded > 0) {
			// check
			if (quantity > quantityNeeded) {
				quantity = quantityNeeded;
			}
			// Ideally:: At this point here, you want to add gold to player economy
			
			marketRequest.Remove(resource, quantity);
		}

		marketPlaceBuffer.Remove(resource, quantity);
		bufferResources = marketPlaceBuffer.Contains();
		// magic completed
	}
}
