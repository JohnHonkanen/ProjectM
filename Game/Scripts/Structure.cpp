#include "Structure.h"

using namespace std;


Structure::Structure() {

}

Structure::~Structure()
{
}

//Structure::Structure(string building, int hp, int pow, int eff, int radOut, vec3 position, bool placed, bool active)
//{
//	building = name;
//	hp = health;
//	pow = powerUsage;
//	eff = productionEfficiency;
//	radOut = radiationOutput;
//	position = pos;
//	placed = isPlaced;
//	active = isActive;
//}

Structure::Structure(string building)
{
}

Structure * Structure::Create(string building, int hp, int pow, int eff, int rad, vec3 position, bool placed, bool active)
{
	Structure *s = new Structure(building, hp, pow, eff, rad, position, placed, active);
	return s;
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

vec3 Structure::GetPos()
{
	return pos;
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

void Structure::SetPos(vec3 change)
{
	pos = change;
}

void Structure::SetPlaced(bool change)
{
	isPlaced = change;
}

void Structure::SetActive(bool change)
{
	isActive = change;
}


Structure::Structure(string building, int hp, int pow, int eff, int radOut, vec3 position, bool placed, bool active)
{
	name = building;
	health = hp;
	powerUsage = pow;
	productionEfficiency = eff;
	radiationOutput = radOut;
	pos = position;
	isPlaced = placed;
	isActive = active;
}



