/*
Warehouse class used to store and send/recieve resources
Dev: Jack Smith (B000308927)
*/

#include "Warehouse.h"

using namespace std;

//needs create method - X

//copy method - X

//serialization code please - X

Warehouse::Warehouse() {
	delete[] inv;
}

Warehouse::~Warehouse()
{
}

Warehouse::Warehouse(string buildingName, int hp, int pow, int eff, int radOut, vec3 position, bool placed, bool active)
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

Warehouse * Warehouse::Create(GameObject * gameObject, string name, int hp, int pow, int eff, int rad, vec3 position, bool placed, bool active)
{
	Warehouse *w = new Warehouse(name, hp, pow, eff, rad, position, placed, active);
	gameObject->AddComponent(w);
	return w;
}

void Warehouse::Copy(GameObject * copyObject)
{
	Warehouse * copy = new Warehouse();
	copy->health = Warehouse::health;
	copy->powerUsage = Warehouse::powerUsage;
	copy->productionEfficiency = Warehouse::productionEfficiency;
	copy->radiationOutput = Warehouse::radiationOutput;
	copy->pos = Warehouse::pos;
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
	inv->SetStorageSize(change);
}
