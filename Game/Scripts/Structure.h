#pragma once

#include "components\Behaviour.h"
#include "core/GameObject.h"
#include "Inventory.h"
#include <cereal\cereal.hpp>
#include <cereal\types\polymorphic.hpp>
#include <vector>
#include <cstring>

using namespace std;
using namespace glm;

class Structure : public Behaviour {
protected:

	int health;						//Buildings remaining health
	int powerUsage;					//Set to 0 until power is added to game
	int productionEfficiency;		//
	int radiationOutput;			//
	bool isPlaced;					//
	bool isActive;					//Turn on or off building
	string name;
	string type;

	std::unique_ptr<Inventory> inv = std::make_unique<Inventory>();

public:
	

	Structure();
	~Structure();
	Structure(string building, string typ, int hp, int pow, int eff, int radOut, bool placed, bool active);
	Structure(string building);

	void Copy(GameObject *copyObject) {};

	string GetName() { return name; }
	int  GetHealth();				//Returns building health
	int  GetPowerusage();			//Returns power usage
	int  GetProductionEfficiency();	//
	int  GetRadiationOutput();		//
	bool GetPlaced();				//
	bool GetActive();				//

	void SetName(string change);
	void SetHealth(int change);				//Changes buildings health
	void setPowerUsage(int change);			//Changes building power usage
	void SetProductionEfficiency(int change);	//Changes buildings
	void SetRadiationOutput(int change);		//
	void SetPlaced(bool change);				//
	void SetActive(bool change);				//

	void InsertItem(Resources res);
	Inventory* GetInventory() { return inv.get(); }
	void SendItem(std::vector<Resources> originInv, std::vector<Resources> destInv, Resources res, int index);
	string ViewInventory() { return inv->DisplayContents(); }

	void OnLoad();
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