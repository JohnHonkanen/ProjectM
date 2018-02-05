/*
The Structure Manager class used to create and manage structures
Dev: Jack Smith (B000308927)
*/

#include "BuildingManager.h"
#include "Production.h"
#include "Warehouse.h"
#include "core\GameEngine.h"
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

//based on get texture in texture manager
Structure BuildingManager::CreateNewBuilding(Structure * object)//this needs to return something, not be void
{
	auto it = buildingList.find("RANDOMNANE");
	if (it != buildingList.end()) {
		return buildingList["RANDOMNANE"]->Instantiate();
	}

	assert(0);//this should never happen
}
//be in get method
//void BuildingManager::CounterIncrease(string building)
//{
//	if (building == "dome") { domeCounter++; }
//	else if (building == "factory") { factoryCounter++; }
//	else if (building == "warehouse") { warehouseCounter++; }
//}
//int BuildingManager::GetCounter(string building)
//{
//	if (building == "dome") { return domeCounter; }
//	else if (building == "factory") { return factoryCounter; }
//	else if (building == "warehouse") { return warehouseCounter; }
//}

void BuildingManager::CreateStructure(STRUCTURE_TYPE type, std::string request)
{
	GameObject* gameObject = GameEngine::manager.gameObjectManager->CreateGameObject("RANDOMNAME");

	switch (type)
	{
	case BuildingManager::PRODUCTION:
		//make create in specific locations
		Production::Create(gameObject, "RANDOMNANE", 10, 1, 1, 1, vec3(0, 0, 0), true, true);
		break;
	case BuildingManager::WAREHOUSE:
		Warehouse::Create(gameObject, "RANDOMNANE", 10, 1, 1, 1, vec3(0, 0, 0), true, true);
		break;
	default:
		break;
	}

	nextName = request /*+ " " + to_string(GetCounter(request))*/;
	//CounterIncrease(request);
	buildingList.insert(pair<string, GameObject*>(gameObject->name, gameObject));

}