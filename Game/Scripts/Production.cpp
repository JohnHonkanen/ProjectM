/*
Production Class - Used for maintaing any building type that produces resources.

Dev: Greg Smith (B00308929)
*/

#include "Production.h"
#include "utility\Clock.h"

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
	isActive = active;
	resourceManager = resourceMan;
	this->hub = hub;
}

Production * Production::Create(string name, StructureType typ, int hp, int pow, int eff, int up, int cost,
								int rad, bool placed, bool active, ResourceManager * resourceMan, Hub * hub)
{
	Production *p = new Production(name, typ, hp, pow, eff, up, rad, placed, active, resourceMan, hub);
	if (typ = DOME) {
		p->inventory = v2::Inventory(1);
	}
	if (typ = FACTORY) {
		p->inventory = v2::Inventory(2);
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
	copy->structureType = structureType;
	copy->resourceManager = resourceManager;
	copy->hub = hub;
	copy->inventory.SetResourceManager(resourceManager);
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
		if (structureType = DOME) {
			if (isProducing) {
				int availableSpace = inventory.CheckStorageFull(producing);
				if (availableSpace > 0) {
					Resources* r = resourceManager->Find(producing);
					int productionAmount = floor((r->GetStackLimit()*0.25)*productionEfficiency);
					inventory.AddItem(producing, productionAmount);
					billboard->Spawn();
				}
			}
		}
		else if (structureType = FACTORY) {
			if (isProducing) {
				int availableSpace = inventory.At(0).quantity;
				if (availableSpace > 0) {
					Resources* r = resourceManager->Find(producing);
					int productionAmount = floor((r->GetStackLimit()*0.25)*productionEfficiency);
					inventory.AddItem(producing, productionAmount);
					billboard->Spawn();
				}
			}
		}

		if (task.GetType() == TASK_TYPE::NONE)
		{
			if (inventory.At(0).quantity > 0)
			{
				task = v1::TaskSystem::Task(TASK_TYPE::COLLECT,5, this, nullptr, inventory.At(0).resource->GetResouceID(), 0);
				hub->GetTaskManager()->AddTask(task, 5);
			}
		}
		
		clock.ResetClock();
	}
}

//this method will be used when declaring what item a building is producing
//and limiting it to the correct items
void Production::SetProduction(ResourceName type)
{
		producing = type;
		billboard->SetTextureToDisplay(resourceManager->Find(producing)->GetResourceIcon());
}

void Production::SetActive(bool change)
{
	isActive = change;
	isProducing = change;
}
 