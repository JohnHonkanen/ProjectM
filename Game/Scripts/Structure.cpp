/*
Structure class that maintains the base properties off all structures

Devs: Jack Smith (B00308927) & Greg Smith (B00308929)
*/

#include "Structure.h"

using namespace std;

Structure::Structure() {

}

Structure::~Structure()
{
}

Structure::Structure(string building, string typ, int hp, int pow, int eff, int radOut, bool placed, bool active)
{
	
	name = building;
	type = typ;
	health = hp;
	powerUsage = pow;
	productionEfficiency = eff;
	radiationOutput = radOut;
	isPlaced = placed;
	isActive = active;
}

Structure::Structure(string building)
{
}

void Structure::OnLoad()
{
}

int Structure::GetHealth()
{
	return health;
}

int Structure::GetPowerusage() {
	return powerUsage;
}

int Structure::GetProductionEfficiency()
{
	return productionEfficiency;
}

int Structure::GetRadiationOutput()
{
	return radiationOutput;
}

bool Structure::GetPlaced()
{
	return isPlaced;
}

bool Structure::GetActive()
{
	return isActive;
}

void Structure::SetName(string change)
{
	name = change;
}

void Structure::SetHealth(int change)
{
	health -= change;
}

void Structure::setPowerUsage(int change)
{
	powerUsage += change;
}

void Structure::SetProductionEfficiency(int change)
{
	productionEfficiency *= change;
}

void Structure::SetRadiationOutput(int change)
{
	radiationOutput *= change;
}

void Structure::SetPlaced(bool change)
{
	isPlaced = change;
}

void Structure::SetActive(bool change)
{
	isActive = change;
}

/*
Wrapper method that Inserts an item into the inventory of the Warehouse.

@param - The resource to be inserted.
*/
void Structure::InsertItem(Resources res)
{
	inv->PlaceItem(res);
	if (!inv->GetStorageFull())
	{
		inv->SendItem(res, inv->GetAtStorageIndex());
	}
}

/*
	Does the sending of an item from one building to another


*/
void Structure::SendItem(std::vector<Resources> originInv, std::vector<Resources> destInv, Resources res)
{
	//destInv->PlaceItem(res);
}
