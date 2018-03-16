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

Production * Production::Create(string name, StructureType typ, int hp, int pow, int eff, int up,
								int rad, bool placed, bool active, ResourceManager * resourceMan, Hub * hub)
{
	Production *p = new Production(name, typ, hp, pow, eff, up, rad, placed, active, resourceMan, hub);
	p->inventory = v2::Inventory(1);
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
	copy->radiationOutput = Production::radiationOutput;
	copy->isPlaced = Production::isPlaced;
	copy->isActive = Production::isActive;
	copy->structureType = structureType;
	copy->resourceManager = resourceManager;
	copy->hub = hub;
	copyObject->AddComponent(copy);
}

void Production::Start()
{
	clock.SetDelay(1000);		//sets alarm
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
		
		if (isProducing) {
			int availableSpace = 0;
			
			if (!inventory.CheckStorageFull(resourceManager->Find(producing),availableSpace)) {
				int amount = 10;
				inventory.AddItem(producing, amount);
				billboard->Spawn();
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