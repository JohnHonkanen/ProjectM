/*
Structure class that maintains the base properties off all structures

Dev: Greg Smith (B00308929)
*/
#pragma once

#include "components\Behaviour.h"
#include "core/GameObject.h"
#include "InventoryV2.h"
#include <cereal\cereal.hpp>
#include <cereal\types\polymorphic.hpp>
#include <vector>
#include <cstring>
#include "task_system\Task.h"
#include "Drone.h"
#include "task_system/drones/DroneController.h"

using namespace std;
using namespace glm;

enum StructureType
{
	PRODUCTION,
	WAREHOUSE,
	FACTORY, 
	DOME,
	HUB,
	DOCK,
	UNBUILDABLEZONE,
};

class Structure : public Behaviour {
protected:

	int health;													//Structures health, damaged by environment(*), effects production Structures productivity(*)
	int powerUsage;												//Power usage of buidings
	int productionEfficiency;									//Level of Structure(1-10), Adjustable in Hud, effects production amount
	int radiationOutput;										//Radiation output of Structure(*)
	int initialUpkeep;											//Upkeep of Structure upon construction, used when reseting Structure level
	int cost;													//Cost of construction for Structure
	int upkeep;													//Current upkeep of Structure, based on level
	bool isPlaced;												//Maintains if the Structure is in a placed state
	bool isActive=false;										//Activity of Structure, can be toggled on and off in Hud
	string name;												//Structure name, adjustable(*)
	string type;										

	int tileX, tileY;											//Structures position
	int tileWidth = 1;											//Structures tile width on the grid
	StructureType structureType;								//Type of Structure
	v2::Inventory inventory;									//Output inventory of Structure

	v1::TaskSystem::Task task;

	vector<v1::TaskSystem::DroneController*> registeredDrones;// List of drones registered to the Structure
public:
	
	Structure();
	~Structure();
	Structure(string building, string typ, int hp, int pow, int eff,int up, int cost, int radOut, bool placed, bool active);
	Structure(string building, string typ, int hp, int pow, int eff, int up, int cost, int radOut, bool placed, bool active, int tileWidth);
	Structure(string building);

	void Copy(GameObject *copyObject) {};					
	void OnLoad();

	string GetName() { return name; }							//Returns the name of the Structure
	int  GetHealth();											//Returns Structure health
	int  GetPowerusage();										//Returns power usage
	int  GetProductionEfficiency();								//Returns production efficiency
	int  GetRadiationOutput();									//Returns radiation output
	int GetUpkeep() { return upkeep; }							//Returns the Structures gold upkeep
	int GetInitialUpkeep() { return initialUpkeep; }			//Returns the Structures initialized upkeep
	int GetCost() { return cost; }								//Returns the cost of construction of the Structure
	bool GetPlaced();											//Returns if the Structure has been placed
	bool GetActive();											//Returns if the Structure is active
	void GetTilePosition(int &x, int &y);						//Returns Structures position
	StructureType GetType();									//Returns Structure type
	v2::Inventory& GetInventory();								//Returns Structure inventory
	int GetTileWidth() { return tileWidth; };					//Returns the tile width of the Strucutre
	void SetTileWidth(int tw) { tileWidth = tw; }				// Sets the tile width of the Structure

	void SetName(string change);								//Sets Structures name, Used when customising Structure(*)
	void SetHealth(int change);									//Changes Structures health
	void setPowerUsage(int change);								//Changes Structure power usage
	void SetProductionEfficiency(int change);					//Changes Structures level
	void SetRadiationOutput(int change);						//Changes Structure radiation output
	void SetUpkeep(int change);									//Changes Structures upkeep
	void SetPlaced(bool change);								// Sets the places state of the Structure
	virtual void SetActive(bool change);						//Toggles Structures activity
	void SetTilePosition(int x, int y);							// Sets the tile position of a Structure
	void RegisterDroneToStructure(v1::TaskSystem::DroneController* drone); // Registers a drone to a Structure
	void DeRegisterDroneToStructure(v1::TaskSystem::DroneController* drone); // DeRegisters a drone to a Structure
	int FindRegisteredDrone(v1::TaskSystem::DroneController* drone) const; // Find a drone registered to a Structure
	vector<v1::TaskSystem::DroneController*> GetRegisteredDrones() { return registeredDrones; } // Returns the list of drones registered to a Structure

	virtual void TaskCompleted(TASK_TYPE type, int index); // Completes the task passed in
	virtual void IncreaseTaskNumber(TASK_TYPE type, int index); // Increases the task number of the given task

	virtual vec3 ParkingLocation();								//Returns the position where a drone will park above a Structure
	virtual int Deposit(ResourceName resource, int amount, int index);		//Adds an item to the Structures inventory of quantity amount
	virtual int Collect(ResourceName resource, int amount, int index);		//Removes an amount of a resource after checking if the inventory holds as much as is being requested, if it does not it takes what is available
	virtual int Contains(ResourceName resource);				//checks how much of an resource is stored in the inventory

	template<class Archive>
	void serialize(Archive & ar)
	{
		CEREAL_NVP(health), CEREAL_NVP(powerUsage), CEREAL_NVP(productionEfficiency), CEREAL_NVP(radiationOutput), CEREAL_NVP(isPlaced);
	}
};

#include <cereal/archives/xml.hpp>
//Register Production as a derived class
CEREAL_REGISTER_TYPE(Structure);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Structure, Behaviour);

//In the event that the copy method is copying a reference/pointer type (or any other method that is doing something similar) remember the referenece cannot be copied
//so a new reference to the same location must be created