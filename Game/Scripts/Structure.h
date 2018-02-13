#pragma once

#include "components\Behaviour.h"
#include "core/GameObject.h"
#include <cereal\cereal.hpp>
#include <cereal\types\polymorphic.hpp>
#include <array>
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

	vec3 pos;						//Buildings position on grid
	bool isPlaced;					//
	bool isActive;					//Turn on or off building

	std::vector<string> storage;
	//std::array<string, 9> storage; //std::array used for storing objects - used because accesing size is easy with it.
	bool storageFull = false;
	int itemsStored = 0;

	int levelModifier = 1;

public:
	string name, type;

	Structure();
	~Structure();
	Structure(string building, string typ, int hp, int pow, int eff, int rad, vec3 position, bool placed, bool active);
	Structure(string building);

	void Copy(GameObject *copyObject) {};

	string GetName() { return name; }
	string GetType() { return type; };
	int  GetHealth();				//Returns building health
	int  GetPowerusage();			//Returns power usage
	int  GetProductionEfficiency();	//
	int  GetRadiationOutput();		//
	vec3 GetPos();					//
	bool GetPlaced();				//
	bool GetActive();				//

	void SetName(string change);
	void SetHealth(int change);				//Changes buildings health
	void setPowerUsage(int change);			//Changes building power usage
	void SetProductionEfficiency(int change);	//Changes buildings
	void SetRadiationOutput(int change);		//
	void SetPos(vec3 change);					//
	void SetPlaced(bool change);				//
	void SetActive(bool change);				//

	string DisplayContents();
	void SetStorageSize(int change) { storage[9 + change]; }
	int GetItemsStored() { return itemsStored; }

	void SendItem();
	void ReceiveItem();
	bool CheckItem(string itemType);
	string PlaceItem(string resource);

	void OnLoad();
	template<class Archive>
	void serialize(Archive & ar)
	{
	   CEREAL_NVP(health), CEREAL_NVP(powerUsage), CEREAL_NVP(productionEfficiency), CEREAL_NVP(radiationOutput), CEREAL_NVP(pos), CEREAL_NVP(isPlaced), CEREAL_NVP(isActive);
	}
};

//In the event that the copy method is copying a reference/pointer type (or any other method that is doing something similar) remember the referenece cannot be copied
//so a new reference to the same location must be created