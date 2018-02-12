/* 
Structure class that maintains the base properties off all structures

Devs: Jack Smith (B00308927) & Greg Smith (B00308929)
*/

#pragma once

#include "components\Behaviour.h"
#include "core/GameObject.h"
#include "Inventory.h"
#include <cereal\cereal.hpp>
#include <cereal\types\string.hpp>
#include <cereal\types\polymorphic.hpp>
#include <vector>

using namespace std;
using namespace glm;

class Structure : public Behaviour {

protected:

	int health;						//Buildings remaining health
	int powerUsage;					//Set to 0 until power is added to game
	int productionEfficiency;		
	int radiationOutput;			
	bool isPlaced;					
	bool isActive;					//Turn on or off building

	int levelModifier = 1;

	Inventory *inv;

public:
	string name;


	Structure();
	~Structure();
	Structure(string building, int hp, int pow, int eff, int rad, bool placed, bool active);
	Structure(string building);


	virtual Structure* Create(string name, int hp, int pow, int eff, int rad, bool placed, bool active) = 0;
	virtual void Copy(GameObject *copyObject) = 0;

	string GetName() { return name; }
	int  GetHealth();				//Returns building health
	int  GetPowerusage();			//Returns power usage
	int  GetProductionEfficiency();	// Returns production efficiency
	int  GetRadiationOutput();		// Returns radiation output
	bool GetPlaced();				// Returns placed state
	bool GetActive();				// Returns active state

	void SetName(string change);
	void SetHealth(int change);				//Changes buildings health
	void setPowerUsage(int change);			//Changes building power usage
	void SetProductionEfficiency(int change);	//Changes buildings
	void SetRadiationOutput(int change);		// Sets radiation output
	void SetPlaced(bool change);				// Sets Placed state
	void SetActive(bool change);				// Sets active state


	void OnLoad();
	template<class Archive>
	void serialize(Archive & ar)
	{
	   CEREAL_NVP(health), CEREAL_NVP(powerUsage), CEREAL_NVP(productionEfficiency), CEREAL_NVP(radiationOutput), CEREAL_NVP(isPlaced), CEREAL_NVP(isActive);
	}
};

//In the event that the copy method is copying a reference/pointer type (or any other method that is doing something similar) remember the referenece cannot be copied
//so a new reference to the same location must be created

#include <cereal/archives/xml.hpp>
//Register Structure as a derived class
CEREAL_REGISTER_TYPE(Structure);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Behaviour, Structure);