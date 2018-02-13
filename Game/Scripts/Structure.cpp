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

Structure::Structure(string name)
{
}

Structure::Structure(string name, int hp, int pow, int eff, int radOut, bool placed, bool active)
{
	this->name = name;
	this->health = hp;
	this->powerUsage = pow;
	this->productionEfficiency = eff;
	this->radiationOutput = radOut;
	this->isPlaced = placed;
	this->isActive = active;
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

//string Structure::DisplayContents()
//{
//	string contents;
//
//	for (int i = 0; i < storage.size; i++)
//	{
//		contents += storage[i];
//	}
//
//	return contents;
//}

string Structure::DisplayContents()
{
	string contents;

	for (auto it = storage.begin(); it != storage.end(); ++it)
	{
		contents += *it;
	}

	return contents;
}

/*
Sends resource to another building
*/
void Structure::SendItem()
{
}
/*
Receives resource from another building and stores it in the warehouse storage
*/
void Structure::ReceiveItem()
{
}

/*
Checks the warehouse storage against the item to see if it has space for the item and whether it can store the item type.

@param - itemType - The type of resource to be sent to the Warehouse

@returns true if the itemType is acceptable to the Warehouse, false if not.
*/
bool Structure::CheckItem(string itemType)
{
	/*
	Checks the item type against a list of acceptable item types.
	*/
}

/*
If checkitem succeeds, the item is placed at a new slot in the vector.
*/
string Structure::PlaceItem(string resource)
{
	string report;

	if (storage.size() < 9 * levelModifier)
	{
		storage.push_back(resource);

		report = "Item placed in " + storage.size();
	}

	else
	{
		report = "Storage full";
	}
	
	return report;
}



