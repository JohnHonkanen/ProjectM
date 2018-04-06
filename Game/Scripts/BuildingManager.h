/*
The Building Manager class used to create and manage structures
Devs: Jack Smith (B00308927), Greg Smith (B00308929), John Honkanen (B00291253)
*/
#pragma once
#include <map>
#include <memory>
#include <cereal\cereal.hpp>
#include <cereal\types\map.hpp>
#include "Structure.h"
#include "ResourceManager.h"

using namespace std;
typedef unique_ptr<Structure> BuildingObjectUniquePointer;

class BuildingManager {
public:
	BuildingManager();						// Deafult constructor
	~BuildingManager();						// Deafult destructor

	//Create Method(gameobject)
	/*
	Called after loading all objects
	*/
	void Start();

	GameObject* CreateNewBuilding(Structure * object, string asset);
	GameObject* GetBuilding(string name);


	void SearchWarehouses(map<string, unique_ptr<GameObject>> buildings);
	void SetResourceManager(ResourceManager * resourceManager);
	// Removes the building type from the buildingList
	void RemoveBuilding(Structure * building);
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(CEREAL_NVP(buildingList));
	}
private:
	ResourceManager * resourceManager;
	map<string, unique_ptr<GameObject>> buildingList;			// map struct used to store a structure related to a specific structure name from a file : original
};