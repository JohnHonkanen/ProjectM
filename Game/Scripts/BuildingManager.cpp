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
using namespace std;

BuildingManager::BuildingManager()
{
}
BuildingManager::~BuildingManager()
{
}

void BuildingManager::Start()
{

	//Basic Factory
	CreateNewBuilding(
		Production::Create("Factory 1","Factory", 10, 1, 1, 1, false, false, resourceManager),
		"AssetPath"
	);

	//Basic Factory
	CreateNewBuilding(
		Production::Create("Dome 1", "Dome", 10, 1, 1, 1, false, false, resourceManager),
		"AssetPath"
	);

	//Radiation Factory
	CreateNewBuilding(
		Production::Create("Factory 2","Radiation Factory", 10, 1, 1, 1000, false, false, resourceManager),
		"AssetPath"
	);

	GameObject * object = GetBuilding("Radiation Factory");
	object->transform->SetPosition(vec3(100,0,10));
	object->transform->Scale(vec3(1.0));

}

//based on get texture in texture manager
GameObject* BuildingManager::CreateNewBuilding(Structure * cStructure, string asset)//this needs to return something, not be void
{

	auto it = buildingList.find(cStructure->GetName());
	if (it == buildingList.end()) {
		//Create the structure
		GameObject *structure = new GameObject(cStructure->GetName());
		structure->AddComponent(cStructure); //Component Structure
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
