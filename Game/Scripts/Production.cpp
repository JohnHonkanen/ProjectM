/*
Production Class - Used for maintaing any building type that produces resources.

Dev: Greg Smith (B00308929)
*/

#include "Production.h"
#include "utility\Clock.h"
#include "GameManager.h"

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
	copy->cost = cost;
	copy->radiationOutput = Production::radiationOutput;
	copy->isPlaced = Production::isPlaced;
	copy->isActive = Production::isActive;
	copy->isProducing = Production::isProducing;
	copy->structureType = structureType;
	copy->resourceManager = resourceManager;
	copy->hub = hub;
	copy->inventory.SetResourceManager(resourceManager);
	copy->tileWidth = tileWidth;
	//copy->inventory = inventory;
	//copy->inventory2 = inventoryOutput;
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

void Production::Update(double currentTime)
{
	clock.UpdateClock();//updating clock time

	if (clock.Alarm()) {//check if alarm has gone off
		if (inventory.At(0).quantity > 0) {
			if (producing != inventory.At(0).resource->GetResouceID()) {

			}
		}
		else {
			int availableSpace = inventory.CheckStorageFull(producing);
			if (structureType == DOME && isProducing) {
				if (availableSpace > 0) {
					Resources* r = resourceManager->Find(producing);
					int productionAmount = floor((r->GetStackLimit()*0.25)*productionEfficiency);
					inventory.AddItem(producing, productionAmount);
					billboard->Spawn();
				}
			}
			else if (structureType == FACTORY && isProducing && inventory.Contains(inputResource) > 0) {//change 0 to resources production ratio
				if (availableSpace > 0) {
					Resources* r = resourceManager->Find(producing);
					int productionAmount = floor((r->GetStackLimit()*0.25)*productionEfficiency);
					inventory.AddItem(producing, productionAmount);
					billboard->Spawn();
				}
			}
		}
		if (structureType == DOME) {
			if (task.GetType() == TASK_TYPE::NONE)
			{
				if (inventory.At(0).quantity > 0)
				{
					task = v1::TaskSystem::Task(TASK_TYPE::COLLECT, 5, this, this, inventory.At(0).resource->GetResouceID(), 0);
					hub->GetTaskManager()->AddTask(task, task.GetPriority());
				}
			}
		}
		else if (structureType == FACTORY) {
			if (task.GetType() == TASK_TYPE::NONE)
			{
				if (inventory.At(0).quantity > 0)
				{
					task = v1::TaskSystem::Task(TASK_TYPE::COLLECT, 10, this, this, inventory.At(0).resource->GetResouceID(), 0);
					hub->GetTaskManager()->AddTask(task, task.GetPriority());
				}
			}
			if (request.GetType() == TASK_TYPE::NONE && isProducing)
			{
				request = v1::TaskSystem::Task(TASK_TYPE::REQUEST, 15, this, nullptr, inputResource, 100);
				hub->GetTaskManager()->AddTask(request, request.GetPriority());
			}
		}
		clock.ResetClock();
	}
}

void Production::SetProduction(ResourceName type)
{
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

//void ProductionLine() {
//	int availableSpace = inventory.CheckStorageFull(producing);
//	if (structureType == DOME && isProducing) {
//		if (availableSpace > 0) {
//			Resources* r = resourceManager->Find(producing);
//			int productionAmount = floor((r->GetStackLimit()*0.25)*productionEfficiency);
//			inventory.AddItem(producing, productionAmount);
//			billboard->Spawn();
//		}
//	}
//	else if (structureType == FACTORY && isProducing && inventory.Contains(inputResource) > 0) {//change 0 to resources production ratio
//		if (availableSpace > 0) {
//			Resources* r = resourceManager->Find(producing);
//			int productionAmount = floor((r->GetStackLimit()*0.25)*productionEfficiency);
//			inventory.AddItem(producing, productionAmount);
//			billboard->Spawn();
//		}
//	}
//}
 