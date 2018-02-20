/*
Production Class - Used for maintaing any building type that produces resources.

Devs: Jack Smith (B00308927) & Greg Smith (B00308929)
*/

#include "Production.h"

using namespace std;

Production::Production() {

}

Production::~Production()
{
}

Production::Production(string buildingName, string typ, int hp, int pow, int eff, 
						int radOut, bool placed, bool active)
{
	name = buildingName;
	type = typ;
	health = hp;
	powerUsage = pow;
	productionEfficiency = eff;
	radiationOutput = radOut;
	isPlaced = placed;
	isActive = active;
}

Production * Production::Create(string name, string typ, int hp, int pow, int eff, 
								int rad, bool placed, bool active)
{
	Production *p = new Production(name, typ, hp, pow, eff, rad, placed, active);
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

	copyObject->AddComponent(copy);
}

void Production::Start()
{
	clock.SetDelay(1000);
	clock.StartClock();
}

void Production::OnLoad()
{
}

void Production::Update(double currentTime)
{
	clock.UpdateClock();//updating clock time

	if (clock.Alarm()) {//check if alarm has gone off
		
		if (GetActive() == true && inv->InventorySize() < 100) {	// if building is active and slot is not full
			inv->PlaceItem(res);									//add x amount of a resource to the local inventory slot
			cout << inv->DisplayContents();							// testing console
		}
		if (storage >= 50) {
			//inv->PlaceItem(res);									//send built up resource to a warehouse
		}
		clock.ResetClock();
	}
}
//

//this method will be used when declaring what item a building is producing
//and limiting it to the correct items
void Production::setProduction(string type, int eff, bool act)
{
	/*if (type == "dome") {
		domeProduction(eff, act);
	
	else if (type == "factory") {
		factoryProduction(eff, act);
	}*/
}


//void Production::setStorage(int change) //Defunct method
//{
//	/*
//	storage = += change;
//	*/
//}

/*to draw building note
MeshRenderer::Create(gameobject, assetpath);
if you want to scale up and down
use the gameobject.transform.scale, translate, rotate
*/