/*
Warehouse class used to store and send/recieve resources
Dev: Jack Smith (B00308927)
*/

#include "Warehouse.h"

using namespace std;

Warehouse::Warehouse() {
	delete[] inv;
}

Warehouse::~Warehouse()
{
}

Warehouse::Warehouse(string buildingName, int hp, int pow, int eff, int rad, bool placed, bool active)
{
	name = buildingName;
	health = hp;
	powerUsage = pow;
	productionEfficiency = eff;
	radiationOutput = rad;
	isPlaced = placed;
	isActive = active;
}

Warehouse * Warehouse::Create(string name, int hp, int pow, int eff, int rad, bool placed, bool active)
{
	Warehouse *w = new Warehouse(name, hp, pow, eff, rad, placed, active);
	w->structureType = WAREHOUSE;
	return w;
}

void Warehouse::Copy(GameObject *copyObject)
{
	Warehouse * copy = new Warehouse();
	copy->name = Warehouse::name;
	copy->health = Warehouse::health;
	copy->powerUsage = Warehouse::powerUsage;
	copy->productionEfficiency = Warehouse::productionEfficiency;
	copy->radiationOutput = Warehouse::radiationOutput;
	copy->isPlaced = Warehouse::isPlaced;
	copy->isActive = Warehouse::isActive;
	copy->structureType = WAREHOUSE;

	copyObject->AddComponent(copy);

}

void Warehouse::OnLoad()
{
}

void Warehouse::Update()
{
}



void Warehouse::Update(int change)
{
	inv->SetInventorySize(change);
}
