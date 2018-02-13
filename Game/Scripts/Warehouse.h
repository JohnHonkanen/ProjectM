/*
Warehouse class used to store and send/recieve resources
Dev: Jack Smith (B00308927)
*/

#include "components\Behaviour.h"
#include "core/GameObject.h"
#include <cereal\cereal.hpp>
#include <cereal\types\string.hpp>
#include <cereal\types\vector.hpp>
#include <cereal\types\polymorphic.hpp>
#include "Structure.h"
#include "Inventory.h"
#include <array>

using namespace std;
using namespace glm;


class Warehouse : public Structure {
private:
	Inventory *inv;

public:
	Warehouse::Warehouse(); 
	Warehouse::~Warehouse();
	Warehouse::Warehouse(string name, int hp, int pow, int eff, int rad, bool placed, bool active);
	static Warehouse * Warehouse::Create(GameObject * gameObject, string name, int hp, int pow, int eff, int rad, bool placed, bool active);
	void Copy(GameObject *copyObject);

	void OnLoad();
	void Update();
	void Update(int change);

	// Serilazation method to store the required variables to an xml document.
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(CEREAL_NVP(storage), CEREAL_NVP(health), CEREAL_NVP(powerUsage), CEREAL_NVP(radiationOutput), CEREAL_NVP(isPlaced), CEREAL_NVP(isActive));
	}
};

using namespace Engine;

#include <cereal/archives/xml.hpp>
//Register Warehouse as a derived class
CEREAL_REGISTER_TYPE(Warehouse);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Structure, Warehouse);