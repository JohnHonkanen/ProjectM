/*
Production Class - Used for maintaing any building type that produces resources.

Dev: Greg Smith (B00308929)
*/

#include "Production.h"
#include "utility\Clock.h"
#include "BuildingProductionAnims.h"


using namespace std;

Production::Production() {

}

Production::~Production()
{
}

Production::Production(string buildingName, StructureType typ, int hp, int pow, int eff,
						int radOut, bool placed, bool active, ResourceManager * resourceMan, Hub * hub)
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
	this->hub = hub;
}

Production * Production::Create(string name, StructureType typ, int hp, int pow, int eff, 
								int rad, bool placed, bool active, ResourceManager * resourceMan, Hub * hub)
{
	Production *p = new Production(name, typ, hp, pow, eff, rad, placed, active, resourceMan, hub);
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
	copy->hub = hub;
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
		Resources temp = resourceManager->FindResource(GetProduction());//temp resource object for quantity change

		//int inventoryLimit = inv->GetResourceAtIndex(0).GetItemAmount();	//Finds out volume of resource in inventory slot
		if(GetActive() == true && producing > 0 && inv->GetInventory().empty()) {
			Resources temp = resourceManager->FindResource(GetProduction());//temp resource object for quantity change
			temp.IncreaseItemAmount(/*1+GetProductionEfficiency()*/10);			//sets value of item created
			inv->PlaceItem(temp);
			BuildingProductionAnims * bpa = gameObject->GetComponent<BuildingProductionAnims>();//calls component
			bpa->SetTextureToDisplay(temp.GetResourceIcon());//gets icon image 
			bpa->Spawn(); // makes icon appear when an item is made

		}
		else if (GetActive() == true && producing > 0) {	// if building is active and slot is not full compared to previous obtained value
			if (inv->GetResourceQuantityAtIndex(0) < 100) {
				temp.IncreaseItemAmount(/*1+GetProductionEfficiency()*/10);			//sets value of item created
				inv->PlaceItem(temp);											//passes temp resource to place item wrapper for inventory
			}
			cout << inv->DisplayInventory() << endl;
			if (inv->GetResourceQuantityAtIndex(0) >= 50) {
				int x, y;
				this->GetTilePosition(x, y);
				Structure *nearest = hub->FindNearest(StructureType::WAREHOUSE, x, y);
				if (nearest != nullptr) {
					auto destinationInv = nearest->GetInventory();
					inv->SendItem(inv.get(), destinationInv, inv->GetResourceAtIndex(0), 0);									//send built up resource to a warehouse
				}
			}
		}
		clock.ResetClock();
	}
}

void Production::StoreItem(Resources res) {
	inv->PlaceItem(res);									//add x amount of a resource to the local inventory slot
	cout << inv->DisplayInventory();							// testing console
}

//this method will be used when declaring what item a building is producing
//and limiting it to the correct items
void Production::SetProduction(int type)
{
	//if (producing != type) {
	//	//clear inventory, inventory needs to ignore remove @ index if its nullptr - quote Chris
	//	inv->RemoveAtIndex(0);
	//}
		producing = type;
}
//Returns the name of the current item set for production
string Production::GetProductionName()
{	
	string production = resourceManager->FindResource(GetProduction()).GetName();
	return production;
}
