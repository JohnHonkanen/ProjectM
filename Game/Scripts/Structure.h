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
};

class Structure : public Behaviour {
protected:

	int health;													//Buildings health, damaged by environment(*), effects production buildings productivity(*)
	int powerUsage;												//Power usage of buidings
	int productionEfficiency;									//Level of building(1-10), Adjustable in Hud, effects production amount
	int radiationOutput;										//Radiation output of building(*)
	int initialUpkeep;											//Upkeep of building upon construction, used when reseting building level
	int cost;													//Cost of construction for building
	int upkeep;													//Current upkeep of building, based on level
	bool isPlaced;												//
	bool isActive=false;										//Activity of building, can be toggled on and off in Hud
	string name;												//Building name, adjustable(*)
	string type;										

	int tileX, tileY;											//Buildings position
	int tileWidth = 1;									
	StructureType structureType;								//Type of building
	v2::Inventory inventory;									//Output inventory of building

	v1::TaskSystem::Task task;									//Task system of building
public:
	
	Structure();
	~Structure();
	Structure(string building, string typ, int hp, int pow, int eff,int up, int cost, int radOut, bool placed, bool active);
	Structure(string building, string typ, int hp, int pow, int eff, int up, int cost, int radOut, bool placed, bool active, int tileWidth);
	Structure(string building);

	void Copy(GameObject *copyObject) {};
	void OnLoad();

	string GetName() { return name; }
	int  GetHealth();											//Returns building health
	int  GetPowerusage();										//Returns power usage
	int  GetProductionEfficiency();								//Returns production efficiency
	int  GetRadiationOutput();									//Returns radiation output
	int GetUpkeep() { return upkeep; }							//Returns the buildings gold upkeep
	int GetInitialUpkeep() { return initialUpkeep; }			//Returns the buildings initialized upkeep
	int GetCost() { return cost; }								//Returns the cost of construction of the building
	bool GetPlaced();											//Returns if the building has been placed
	bool GetActive();											//Returns if the building is active
	void GetTilePosition(int &x, int &y);						//Returns buildings position
	StructureType GetType();									//Returns building type
	v2::Inventory& GetInventory();								//Returns building inventory
	int GetTileWidth() { return tileWidth; };
	void SetTileWidth(int tw) { tileWidth = tw; };

	void SetName(string change);								//Sets buildings name, Used when customising building(*)
	void SetHealth(int change);									//Changes buildings health
	void setPowerUsage(int change);								//Changes building power usage
	void SetProductionEfficiency(int change);					//Changes buildings level
	void SetRadiationOutput(int change);						//Changes building radiation output
	void SetUpkeep(int change);									//Changes buildings upkeep
	void SetPlaced(bool change);						
	virtual void SetActive(bool change);						//Toggles buildings activity
	void SetTilePosition(int x, int y);
	virtual void TaskCompleted(TASK_TYPE type, int index);
	virtual void IncreaseTaskNumber(TASK_TYPE type, int index); 

	virtual vec3 ParkingLocation();								//Returns a buildings position
	virtual int Deposit(ResourceName resource, int amount, int index);		//Adds an item to the buildings inventory of quantity amount
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