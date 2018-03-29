/*
Structure class that maintains the base properties off all structures

Devs: Jack Smith (B00308927) & Greg Smith (B00308929)
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
	DOME
};

class Structure : public Behaviour {
protected:

	int health;						//Buildings remaining health
	int powerUsage;					//Set to 0 until power is added to game
	int productionEfficiency;		//Level of building, will be adjustable using buttons, limited between 1 and 10
	int radiationOutput;			//
	int initialUpkeep;
	int cost;
	int upkeep;
	bool isPlaced;					//
	bool isActive;					//Turn on or off building
	string name;
	string type;

	int tileX, tileY;
	int tileWidth = 1;
	StructureType structureType;
	v2::Inventory inventory;

	v1::TaskSystem::Task task;
public:
	
	Structure();
	~Structure();
	Structure(string building, string typ, int hp, int pow, int eff,int up, int cost, int radOut, bool placed, bool active);
	Structure(string building, string typ, int hp, int pow, int eff, int up, int cost, int radOut, bool placed, bool active, int tileWidth);
	Structure(string building);

	void Copy(GameObject *copyObject) {};
	void OnLoad();

	string GetName() { return name; }
	int  GetHealth();				//Returns building health
	int  GetPowerusage();			//Returns power usage
	int  GetProductionEfficiency();	//
	int  GetRadiationOutput();		//
	int GetUpkeep() { return upkeep; } // returns the buildings gold upkeep
	int GetCost() { return cost; }
	bool GetPlaced();				//
	bool GetActive();				//
	void GetTilePosition(int &x, int &y);
	StructureType GetType();
	v2::Inventory& GetInventory();
	int GetTileWidth() { return tileWidth; };
	void SetTileWidth(int tw) { tileWidth = tw; };

	void SetName(string change);
	void SetHealth(int change);				//Changes buildings health
	void setPowerUsage(int change);			//Changes building power usage
	void SetProductionEfficiency(int change);	//Changes buildings
	void SetRadiationOutput(int change);		//
	bool SetUpkeep(int change);					//Used when adjusting the buildings upkeep when using prod ui
	void SetPlaced(bool change);				//
	virtual void SetActive(bool change);				//
	void SetTilePosition(int x, int y);
	void TaskCompleted();

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