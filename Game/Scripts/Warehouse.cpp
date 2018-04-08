/*
Warehouse class used to store and send/recieve resources
Dev: Jack Smith (B00308927)
*/

#include "Warehouse.h"
#include "LightCycle.h"
using namespace std;

Warehouse::Warehouse() {
}

Warehouse::~Warehouse()
{
}
/*
 * When a warehouse is asked for an item it will loop through it's storage and find the item. This 
 * will give it the index it needs and it will recieve the inventory from the building requesting an item.
 */
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

Warehouse * Warehouse::Create(string name, int hp, int pow, int eff, int rad, bool placed, bool active, ResourceManager * rm)
{
	Warehouse *w = new Warehouse(name, hp, pow, eff, rad, placed, active);
	w->structureType = WAREHOUSE;
	w->inventory = Inventory(9);
	w->inventory.SetResourceManager(rm);
	w->rm = rm;
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
	copy->inventory = Inventory(9);
	copy->inventory.SetResourceManager(rm);
	copy->rm = rm;
	copy->tileWidth = tileWidth;
	LightCycle::Create(copyObject);
	copyObject->AddComponent(copy);

}

void Warehouse::OnLoad()
{
}

void Warehouse::Update()
{
}



