/*
The Structure Manager class used to create and manage structures
Dev: Jack Smith (B000308927)
*/

#include "BuildingManager.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

BuildingManager::BuildingManager()
{
}
BuildingManager::~BuildingManager()
{
}

Structure * BuildingManager::LoadFromPrefab(const char * prefab)
{
	//GetStructure(structure_id/name etc..)
	BuildingObjectUniquePointer building;

	std::ifstream is(prefab);
	cereal::XMLInputArchive iArchive(is);
	iArchive(building);

	Structure * obj = building.get();
	building.release();
	CreateNewBuilding(obj);

	return obj;
}

void BuildingManager::CreateNewBuilding(Structure * object)
{
	//Add(STRUCTURE_TYPE, parameters)

}

void BuildingManager::CounterIncrease(string building)
{
	if (building == "dome") { domeCounter++; }
	else if (building == "factory") { factoryCounter++; }
	else if (building == "warehouse") { warehouseCounter++; }
}

int BuildingManager::GetCounter(string building)
{
	if (building == "dome") { return domeCounter; }
	else if (building == "factory") { return factoryCounter; }
	else if (building == "warehouse") { return warehouseCounter; }
}

void BuildingManager::CreateStructure(std::string request)
{
	nextName = request + " " + to_string(GetCounter(request));
	CounterIncrease(request);
	Structure *object = new Structure(nextName);
	buildingList.insert(pair<string, BuildingObjectUniquePointer>(object->name, BuildingObjectUniquePointer(object)));

}

