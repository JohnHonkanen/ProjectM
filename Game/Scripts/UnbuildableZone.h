/*
UnbuildableZone class used to block placement of other buildings
*/

#pragma once
#include "components\Behaviour.h"
#include <cereal\cereal.hpp>
#include <cereal\types\polymorphic.hpp>
#include "Structure.h"

using namespace std;
using namespace glm;


class UnbuildableZone : public Structure {
private:
	ResourceManager *rm;

public:

	UnbuildableZone();
	~UnbuildableZone();
	UnbuildableZone(string buildingName, bool placed);

	static UnbuildableZone * Create(string name, bool placed);
	static UnbuildableZone * Create(GameObject* gameObject, class GameManager* gameManager);

	void Copy(GameObject *copyObject);

	void OnLoad();
	void Update();

	// Serilazation method to store the required variables to an xml document.
	template<class Archive>
	void serialize(Archive & ar)
	{
	 CEREAL_NVP(isPlaced);
	}
};

#include <cereal/archives/xml.hpp>
//Register Production as a derived class
CEREAL_REGISTER_TYPE(UnbuildableZone);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(UnbuildableZone, Structure);
