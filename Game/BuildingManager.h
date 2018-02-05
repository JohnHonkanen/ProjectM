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
	BuildingManager();							// Deafult constructor
	~BuildingManager();						// Deafult destructor

	enum STRUCTURE_TYPE {

		PRODUCTION, 
		WAREHOUSE

	};

	//serialization code
	void OnLoad();
	/*
	Called after loading all objects
	*/
	void Start();
	/*
	Calls on the Input Loop before Update;
	*/
	void Input();
	/*
	Calls the update functions for all GameObjects in the manager
	*/
	void Update();
	/*
	Calls the draw functions for all GameObjects in the manager
	*/
	void Draw();

	Structure* LoadFromPrefab(const char * prefab);
	Structure CreateNewBuilding(Structure * object);
	//void CounterIncrease(string building);
	//int GetCounter(string building);
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(CEREAL_NVP(buildingList));
	}
private:
	void CreateStructure(STRUCTURE_TYPE type, std::string request);		// Creates a new structure using a file name input
	map<string, GameObject*> buildingList;			// map struct used to store a structure related to a specific structure name from a file : original
	//map<string, StructureUniqPtr> gameStructures;
	//map<string, int> counter;
	int domeCounter;
	int factoryCounter;
	int warehouseCounter;
	string nextName;
};