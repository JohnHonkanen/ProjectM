/*
The Building Manager class used to create and manage structures
Devs: Jack Smith (B00308927), Greg Smith (B00308929), John Honkanen (B00291253)
*/

#include "BuildingManager.h"
#include "Production.h"
#include "Warehouse.h"
#include "core\GameEngine.h"
#include "components\MeshRenderer.h"
#include "GameManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include "BuildingProductionAnims.h"
#include "InventoryWrapper.h"

using namespace std;

BuildingManager::BuildingManager()
{
}
BuildingManager::~BuildingManager()
{
}

void BuildingManager::Start()
{

}

//based on get texture in texture manager
GameObject* BuildingManager::CreateNewBuilding(Structure * cStructure, string asset)//this needs to return something, not be void
{

	auto it = buildingList.find(cStructure->GetName());
	if (it == buildingList.end()) {
		//Create the structure
		GameObject *structure = new GameObject(cStructure->GetName());
		structure->AddComponent(cStructure); //Component Structure
		if (cStructure->GetType()==DOME || cStructure->GetType() == FACTORY) {
			BuildingProductionAnims::Create(structure);
		}

		switch (cStructure->GetType())
		{
		case DOME:
			cStructure->SetTileWidth(3);
			break;
		case FACTORY:
			cStructure->SetTileWidth(3);
			break;
		case WAREHOUSE:
			cStructure->SetTileWidth(3);
			break;
		case UNBUILDABLEZONE:
			cStructure->SetTileWidth(3);
			break;
		default:
			//cStructure->SetTileWidth(3);
			break;
		}
		MeshRenderer::Create(structure, asset);
		buildingList[cStructure->GetName()] =  unique_ptr<GameObject>(structure);
	}

	return buildingList[cStructure->GetName()].get();
}
GameObject * BuildingManager::GetBuilding(string name)
{
	auto it = buildingList.find(name);
	if (it == buildingList.end()) {
		return nullptr;
	}

	return buildingList[name].get()->Instantiate();
}

void BuildingManager::SearchWarehouses(map<string, unique_ptr<GameObject>> buildings)
{
	for (auto it = buildings.begin(); it!= buildings.end(); it++)
	{
		if (buildings.at("Warehouse"))
		{
			// Pass the resource to the warehouse.	
		}
	}
}

void BuildingManager::SetResourceManager(ResourceManager * resourceManager)
{
	this->resourceManager = resourceManager;
}

void BuildingManager::RemoveBuilding(Structure* building)
{
	auto it = buildingList.find(building->GetName());

	buildingList.erase(it);

}
