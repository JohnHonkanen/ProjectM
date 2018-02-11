#pragma once
#include "components\Behaviour.h"
#include "core/GameObject.h"
#include <cereal\cereal.hpp>
#include <cereal\types\polymorphic.hpp>
#include "Structure.h"

using namespace std;
using namespace glm;

class Production : public Structure {
private:
	int dt, storage;
public:

	Production();
	~Production();
	Production(string name, string type ,int hp, int pow, int eff, int radOut, vec3 position, bool placed, bool active);
	static Production * Create(string name, string typ, int hp, int pow, int eff, int rad, vec3 position, bool placed, bool active);

	void Copy(GameObject *copyObject);

	void OnLoad();
	void Update();

	void setProduction(string type, int eff, bool act);
	void domeProduction(int eff, bool act);
	void factoryProduction(int eff, bool act);

	//int getStorage();
	//void setStorage(int change); //Defunct method


	// Serilazation method to store the required variables to an xml document.
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(CEREAL_NVP(storage), CEREAL_NVP(health), CEREAL_NVP(powerUsage), CEREAL_NVP(radiationOutput), CEREAL_NVP(pos), CEREAL_NVP(isPlaced), CEREAL_NVP(isActive));
	}
};