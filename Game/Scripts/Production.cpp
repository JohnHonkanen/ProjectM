#include "Production.h"
#include <ctime>

using namespace std;

Production::Production()
{
}

Production::~Production()
{
}

Production::Production(string buildingName, string type, int hp, int pow, int eff, int radOut, vec3 position, bool placed, bool active)
{
	name = buildingName;

	health = hp;
	powerUsage = pow;
	productionEfficiency = eff;
	radiationOutput = radOut;
	pos = position;
	isPlaced = placed;
	isActive = active;
}

Production * Production::Create(string name, string typ, int hp, int pow, int eff, int rad, vec3 position, bool placed, bool active)
{
	Production *p = new Production(name, typ, hp, pow, eff, rad, position, placed, active);
	return p;
}

void Production::Copy(GameObject * copyObject)
{

	Production * copy = new Production();
	copy->storage = Production::storage;
	copy->storageFull = Production::storageFull;
	copy->itemsStored = Production::itemsStored;
	copy->health = Production::health;
	copy->powerUsage = Production::powerUsage;
	copy->productionEfficiency = Production::productionEfficiency;
	copy->radiationOutput = Production::radiationOutput;
	copy->pos = Production::pos;
	copy->isPlaced = Production::isPlaced;
	copy->isActive = Production::isActive;

	copyObject->AddComponent(copy);
}

void Production::OnLoad()
{
}

void Production::Update()
{
	time_t t = time(0);   // get time now
	struct tm * currentTime = localtime(&t);

	if ((dt - (int)currentTime) <= 300) {
		dt = (int)currentTime;
		if (GetActive() == true && storage < 100) {
			storage += (1 * productionEfficiency);
			cout << storage; // testing
		}

		if (storage >= 50) {
			//call warehouse storage update method
		}

	}
}

void Production::setProduction(string type, int eff, bool act)
{
	if (type == "dome") {
		domeProduction(eff, act);
	}
	else if (type == "factory") {
		factoryProduction(eff, act);
	}
}


//void Production::setStorage(int change) //Defunct method
//{
//	/*
//	storage = += change;
//	*/
//}