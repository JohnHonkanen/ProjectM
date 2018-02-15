/*
Production Class - Used for maintaing any building type that produces resources.

Devs: Jack Smith (B00308927) & Greg Smith (B00308929)
*/

#pragma once
#include "components\Behaviour.h"
#include "core/GameObject.h"
#include <cereal\cereal.hpp>
#include <cereal\types\string.hpp>
#include <cereal\types\vector.hpp>
#include <cereal\types\polymorphic.hpp>
#include "Structure.h"
#include "Inventory.h"

using namespace std;
using namespace glm;

class Production : public Structure {
private:
	int dt, storage;
public:

	Production();
	~Production();
	Production(string name, string type ,int hp, int pow, int eff, int radOut, bool placed, bool active);
	static Production * Create(string name, string typ, int hp, int pow, int eff, int rad, bool placed, bool active);

	void Copy(GameObject *copyObject);

	void OnLoad();
	void Update(double currentTime);
	void Draw(GameObject *obj, string name);

	void setProduction(string type, int eff, bool act);
	//void domeProduction(int eff, bool act);
	//void factoryProduction(int eff, bool act);

	//int getStorage();
	//void setStorage(int change); //Defunct method


	// Serilazation method to store the required variables to an xml document.
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(CEREAL_NVP(storage), CEREAL_NVP(health), CEREAL_NVP(powerUsage), CEREAL_NVP(radiationOutput), CEREAL_NVP(isPlaced), CEREAL_NVP(isActive));
	}
};

#include <cereal/archives/xml.hpp>
//Register Production as a derived class
CEREAL_REGISTER_TYPE(Production);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Structure, Production);


