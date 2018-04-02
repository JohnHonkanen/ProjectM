/*
Structure class that maintains the base properties off all structures

Devs: Greg Smith (B00308929)
*/

#include "Structure.h"

using namespace std;

Structure::Structure() {

}

Structure::~Structure()
{
}

Structure::Structure(string building, string typ, int hp, int pow, int eff, int up, int cost, int radOut, bool placed, bool active)
{
	Structure(building, typ, hp, pow, eff, up, cost, radOut, placed, active, 1);
}

Structure::Structure(string building, string typ, int hp, int pow, int eff, int up, int cost, int radOut, bool placed, bool active, int tileWidth)
{
	name = building;
	type = typ;
	health = hp;
	powerUsage = pow;
	productionEfficiency = eff;
	this->cost = cost;
	initialUpkeep = up;
	upkeep = up;
	radiationOutput = radOut;
	isPlaced = placed;
	isActive = active;
	this->tileWidth = tileWidth;
}

Structure::Structure(string building)
{
}

void Structure::SetTilePosition(int x, int y)
{
	tileX = x;
	tileY = y;
}

void Structure::TaskCompleted()
{
	task = v1::TaskSystem::Task();
}

vec3 Structure::ParkingLocation()
{
	return transform->GetPosition();
}

int Structure::Deposit(ResourceName resource, int amount)
{
	inventory.AddItem(resource, amount);

	return 0;
}

int Structure::Collect(ResourceName resource, int amount)
{
	int toRemove = amount;
	int contains = inventory.Contains(resource);
	if (contains < amount)
	{
		toRemove = contains;
	}

	inventory.Remove(resource, toRemove);

	return toRemove;
	
}

int Structure::Contains(ResourceName resource)
{
	return inventory.Contains(resource);
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

void Structure::GetTilePosition(int & x, int & y)
{
	x = tileX;
	y = tileY;
}

StructureType Structure::GetType()
{
	return structureType;
}

v2::Inventory& Structure::GetInventory()
{
	return inventory;
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
	if (productionEfficiency < 10 && productionEfficiency > 1) {
		productionEfficiency += change;
		
		bool temp = SetUpkeep(change);
		if (!temp) {
			productionEfficiency -= change;
		}
		else{
			SetRadiationOutput(change);
		}
	}
}

void Structure::SetRadiationOutput(int change)
{
	if (radiationOutput > 1) {
		radiationOutput += change;
	}
}

bool Structure::SetUpkeep(int change)
{
	if (upkeep < 10 && upkeep > 1) {
		upkeep += change * initialUpkeep;
	}
	return true;
}

void Structure::SetPlaced(bool change)
{
	isPlaced = change;
}

void Structure::SetActive(bool change)
{
	isActive = change;
}