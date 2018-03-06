/*
Production Class - Used for maintaing any building type that produces resources.

Dev: Greg Smith (B00308929)
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
#include "Resources.h"
#include "ResourceManager.h"
#include "utility\Clock.h"`


using namespace std;
using namespace glm;

class Production : public Structure {
private:
	int producing;
	Engine::Utility::Clock clock;
	void StoreItem(Resources res);

	ResourceManager * resourceManager;
public:

	Production();
	~Production();
	Production(string name, StructureType typ,int hp, int pow, int eff, int radOut, bool placed, bool active, ResourceManager * resourceMan);
	static Production * Create(string name, StructureType typ, int hp, int pow, int eff, int rad, bool placed, bool active, ResourceManager * resourceMan);

	void Copy(GameObject *copyObject);

	void Start();
	void OnLoad();
	void Update(double currentTime);

	void SetProduction(int type);
	int GetProduction() { return producing; }
	//void domeProduction(int eff, bool act);
	//void factoryProduction(int eff, bool act);

	//int getStorage();
	//void setStorage(int change); //Defunct method


	// Serilazation method to store the required variables to an xml document.
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(CEREAL_NVP(name), CEREAL_NVP(type), CEREAL_NVP(health), CEREAL_NVP(powerUsage), CEREAL_NVP(radiationOutput), CEREAL_NVP(isPlaced), CEREAL_NVP(isActive), CEREAL_NVP(producing));
	}
};

#include <cereal/archives/xml.hpp>
//Register Production as a derived class
CEREAL_REGISTER_TYPE(Production);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Structure, Production);


