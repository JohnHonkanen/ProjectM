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

Production::Production(string buildingName, StructureType typ, int hp, int pow, int eff,
						int radOut, bool placed, bool active, ResourceManager * resourceMan)
{
	name = buildingName;
	structureType = typ;
	health = hp;
	powerUsage = pow;
	productionEfficiency = eff;
	radiationOutput = radOut;
	isPlaced = placed;
	isActive = active;
	resourceManager = resourceMan;
}

Production * Production::Create(string name, StructureType typ, int hp, int pow, int eff, 
								int rad, bool placed, bool active, ResourceManager * resourceMan)
{
	Production *p = new Production(name, typ, hp, pow, eff, rad, placed, active, resourceMan);
	return p;
}

void Production::Copy(GameObject * copyObject)
{

	Production * copy = new Production();
	copy->name = Production::name;
	copy->health = Production::health;
	copy->powerUsage = Production::powerUsage;
	copy->productionEfficiency = Production::productionEfficiency;
	copy->radiationOutput = Production::radiationOutput;
	copy->isPlaced = Production::isPlaced;
	copy->isActive = Production::isActive;
	copy->structureType = structureType;
	copy->resourceManager = resourceManager;
	copyObject->AddComponent(copy);
}

void Production::Start()
{
	inv->SetInitialStorage(1);
	clock.SetDelay(1000);		//sets alarm
	clock.StartClock();			//starts clock
}

void Production::OnLoad()
{
}

void Production::Update(double currentTime)
{
	clock.UpdateClock();//updating clock time

	if (clock.Alarm()) {//check if alarm has gone off
		//int inventoryLimit = inv->GetResourceAtIndex(0).GetItemAmount();	//Finds out volume of resource in inventory slot
		if (GetActive() == true && producing > 0) {	// if building is active and slot is not full compared to previous obtained value
			Resources temp = resourceManager->FindResource(GetProduction());//temp resource object for quantity change
			if(temp.GetItemAmount()<100){
			temp.IncreaseItemAmount(/*1+GetProductionEfficiency()*/10);			//sets value of item created
			inv->PlaceItem(temp);											//passes temp resource to place item wrapper for inventory
			}
			cout << inv->DisplayContents() << endl;
		}
		if (inv->InventorySize() >= 50) {
			//inv->PlaceItem(res);									//send built up resource to a warehouse
		}
		clock.ResetClock();
	}
}

void Production::StoreItem(Resources res) {
	inv->PlaceItem(res);									//add x amount of a resource to the local inventory slot
	cout << inv->DisplayContents();							// testing console
}

//this method will be used when declaring what item a building is producing
//and limiting it to the correct items
void Production::SetProduction(int type)
{
		producing = type;
}