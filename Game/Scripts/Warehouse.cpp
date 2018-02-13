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

Warehouse::Warehouse(string name, int hp, int pow, int eff, int rad, bool placed, bool active)
{
	this->name = name;
	this->health = hp;
	this->powerUsage = pow;
	this->productionEfficiency = eff;
	this->radiationOutput = rad;
	this->isPlaced = placed;
	this->isActive = active;
}

Warehouse * Warehouse::Create(GameObject * gameObject, string name, int hp, int pow, int eff, int rad, bool placed, bool active)
{
	Warehouse *w = new Warehouse(name, hp, pow, eff, rad, placed, active);
	gameObject->AddComponent(w);
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
