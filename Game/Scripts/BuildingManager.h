/*
The Structure Manager class used to create and manage structures
Dev: Jack Smith (B000308927)
*/
#pragma once
#include <map>
#include <memory>
#include <cereal\cereal.hpp>
#include <cereal\types\map.hpp>
#include "Structure.h"

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

	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(CEREAL_NVP(buildingList));
	}
private:
	map<string, unique_ptr<GameObject>> buildingList;			// map struct used to store a structure related to a specific structure name from a file : original

};