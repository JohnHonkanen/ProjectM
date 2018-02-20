/*
Production Class - Used for maintaing any building type that produces resources.

Devs: Jack Smith (B00308927) & Greg Smith (B00308929)
*/

#include "Production.h"
#include "utility\Clock.h"

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
	p->structureType = PRODUCTION;
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
	copy->structureType = PRODUCTION;

	copyObject->AddComponent(copy);
}

void Production::OnLoad()
{
}

void Production::Update(double currentTime)
{
	//time_t t = time(0);   // get time now
	//struct tm * currentTime = localtime(&t);

	if ((dt - currentTime) >= 300) {
		dt = currentTime;
		if (GetActive() == true && inv->InventorySize() < 100) {
//			setStorage(getStorage() + 1 * eff); 
			//storage being used as a generalised term until proper building storage can be called
			cout << storage; // testing
		}
		if (storage >= 50) {
			//call warehouse storage update method from player
		}
	}
}


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