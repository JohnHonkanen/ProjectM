/*
Production Class - Used for maintaing any building type that produces resources.
*/

#include "Production.h"
#include "utility\Clock.h"
#include "GameManager.h"
#include "LightCycle.h"

using namespace std;


Production::Production() {

}

Production::~Production()
{
}

Production::Production(string buildingName, StructureType typ, int hp, int pow, int eff, int up,
						int radOut, bool placed, bool active, ResourceManager * resourceMan, Hub * hub)
{
	name = buildingName;
	structureType = typ;
	health = hp;
	powerUsage = pow;
	productionEfficiency = eff;
	upkeep = up;
	radiationOutput = radOut;
	isPlaced = placed;
	isActive = false;
	isProducing = false;
	resourceManager = resourceMan;
	this->hub = hub;
}

Production * Production::Create(string name, StructureType typ, int hp, int pow, int eff, int up, int cost,
								int rad, bool placed, bool active, ResourceManager * resourceMan, Hub * hub)
{
	Production *p = new Production(name, typ, hp, pow, eff, up, rad, placed, active, resourceMan, hub);
	if (typ == DOME) {
		p->inventory = v2::Inventory(1);
	}
	if (typ == FACTORY) {
		p->inventory = v2::Inventory(1);
		p->inventoryOutput = v2::Inventory(1);
		p->inventoryOutput.SetResourceManager(resourceMan);
	}
	p->inventory.SetResourceManager(resourceMan);
	p->cost = cost;

	return p;
}

void Production::Copy(GameObject * copyObject)
{
	Production * copy = new Production();
	copy->name = Production::name;
	copy->health = Production::health;
	copy->powerUsage = Production::powerUsage;
	copy->productionEfficiency = Production::productionEfficiency;
	copy->upkeep = Production::upkeep;
	copy->initialUpkeep = Production::upkeep;
	copy->cost = cost;
	copy->radiationOutput = Production::radiationOutput;
	copy->isPlaced = Production::isPlaced;
	copy->isActive = Production::isActive;
	copy->isProducing = Production::isProducing;
	copy->structureType = structureType;
	copy->resourceManager = resourceManager;
	copy->hub = hub;
	copy->tileWidth = tileWidth;
	copy->inventory = v2::Inventory(1);
	copy->inventoryOutput = v2::Inventory(1);
	copy->inventory.SetResourceManager(resourceManager);
	copy->inventoryOutput.SetResourceManager(resourceManager);
	LightCycle::Create(copyObject);
	copyObject->AddComponent(copy);
}

void Production::Start()
{
	clock.SetDelay(5000);		//sets alarm
	clock.StartClock();			//starts clock
	billboard = gameObject->GetComponent<BuildingProductionAnims>();
}

void Production::OnLoad()
{
}

void Production::DomeProduction()
{
	int availableSpace = inventory.CheckStorageFull(producing);
	Resources* r = resourceManager->Find(producing);
	int productionAmount = floor((r->GetProductionRate())*productionEfficiency);
	if (productionAmount > availableSpace) {
		productionAmount = availableSpace;
	}
	if (productionAmount == 0) {
		return;
	}
	if (isProducing && availableSpace > 0) {
		inventory.AddItem(producing, productionAmount);
		billboard->Spawn();
	}
}

void Production::FactoryProduction()
{
	int availableSpace = inventoryOutput.CheckStorageFull(producing);
	Resources* r = resourceManager->Find(producing);
	int productionAmount = floor((r->GetProductionRate())*productionEfficiency);
	if (productionAmount > availableSpace) {
		productionAmount = availableSpace;
	}
	if (productionAmount == 0) {
		return;
	}
	if (isProducing && inventory.Contains(inputResource) >= productionAmount) {//change 0 to resources production ratio
		inventoryOutput.AddItem(producing, productionAmount);
		inventory.Remove(inputResource, productionAmount);
		billboard->Spawn();
	}
}

void Production::Update(double currentTime)
{
	if (!isActive) {
		return;
	}
	clock.UpdateClock();//updating clock time

	if (numCollectTask < maxCollectTask)
	{
		int contains = inventory.Contains(producing);
		if (structureType == FACTORY) {
			contains = inventoryOutput.Contains(producing);
		}
		if (contains > 0)
		{
			task = v1::TaskSystem::Task(TASK_TYPE::COLLECT, 5, this, this, producing, 20);
			hub->GetTaskManager()->AddTask(task, task.GetPriority());
			numCollectTask++;
		}
	}
	if (structureType == FACTORY) {
		if (numRequestTask < maxRequestTask && isProducing)
		{
			request = v1::TaskSystem::Task(TASK_TYPE::REQUEST, 15, this, nullptr, inputResource, 20);
			hub->GetTaskManager()->AddTask(request, request.GetPriority());
			numRequestTask++;
		}
	}
	clock.SetDelay(resourceManager->Find(producing)->GetProductionTimer() * 1000);
	if (clock.Alarm()) {//check if alarm has gone off
		if (structureType == DOME) {
			DomeProduction();
		}
		else if (structureType == FACTORY) {
			FactoryProduction();
		}
		clock.ResetClock();
	}
}

void Production::SetProduction(ResourceName type)
{
	if (producing != type) {
		inventory.Clear();
		inventoryOutput.Clear();
	}
		producing = type;
		if (structureType == FACTORY) {
			inputResource = GameManager::gameManager->recipeManager.GetInput(producing);
		}
		billboard->SetTextureToDisplay(resourceManager->Find(producing)->GetResourceIcon());
		SetActive(true);
}

void Production::SetActive(bool change)
{
	isActive = change;
	isProducing = change;
}

int Production::Deposit(ResourceName resource, int amount, int index)
{
	if (inventory.At(0).resource != nullptr)
	{
		if (inventory.At(0).resource->GetResouceID() != producing)
		{
			inventory.Clear();
		}
	}
	

	if (resource == inputResource)
	{
		inventory.AddItem(resource, amount);
	} 
	
	return 0;
}

int Production::Collect(ResourceName resource, int amount, int index)
{
	if (structureType == DOME) {
		return Structure::Collect(resource, amount, index);
	}
	else{
		int toRemove = amount;
		int contains = inventoryOutput.Contains(resource);
		if (contains < amount)
		{
			toRemove = contains;
		}

		inventoryOutput.Remove(resource, toRemove);

		return toRemove;
	}
}

int Production::GetInputCount()
{
	if (structureType == FACTORY) {
		return inventory.Contains(inputResource);
	}
	return 0;
}

int Production::GetOutputCount()
{
	if (structureType == FACTORY) {
		return inventoryOutput.Contains(producing);
	}
	return inventory.Contains(producing);
}

void Production::TaskCompleted(TASK_TYPE type, int index)
{
	if (type == TASK_TYPE::REQUEST) {
		numRequestTask--;
	}
	else {
		numCollectTask--;
	}
}

void Production::IncreaseLevel()
{
	if (isActive && productionEfficiency < 9) {
		productionEfficiency = productionEfficiency++;
		upkeep = upkeep * 2;

		maxCollectTask = productionEfficiency / 2 + 1;
		maxRequestTask = productionEfficiency / 2 + 1;
	}
}

void Production::DecreaseLevel()
{
	if (isActive && productionEfficiency > 1) {
		productionEfficiency = productionEfficiency--;
		upkeep = upkeep * 0.5;

		maxCollectTask = productionEfficiency / 2 + 1;
		maxRequestTask = productionEfficiency / 2 + 1;
	}
}

void Production::IncreaseTaskNumber(TASK_TYPE type, int index)
{
	if (type == TASK_TYPE::REQUEST) {
		numRequestTask++;
	}
	else {
		numCollectTask++;
	}
}

int Production::GetUpkeep()
{
	return upkeep + resourceManager->Find(producing)->GetProductionCost();
}
