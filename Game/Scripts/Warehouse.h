/*
Warehouse class used to store and send/recieve resources
Dev: Jack Smith (B00308927)
*/

#include "components\Behaviour.h"
#include "core/GameObject.h"
#include <cereal\cereal.hpp>
#include <cereal\types\polymorphic.hpp>
#include "Structure.h"
#include <array>
#include <memory>

using namespace std;
using namespace glm;


class Warehouse : public Structure {
private:
	ResourceManager *rm;

public:
	
	Warehouse(); 
	~Warehouse();
	Warehouse(string name, int hp, int pow, int eff, int radOut, bool placed, bool active);
	static Warehouse * Create(string name,  int hp, int pow, int eff, int rad, bool placed, bool active, ResourceManager * rm);
	
	void Copy(GameObject *copyObject);

	void OnLoad();
	void Update();

	// Serilazation method to store the required variables to an xml document.
	template<class Archive>
	void serialize(Archive & ar)
	{
		CEREAL_NVP(health), CEREAL_NVP(powerUsage), CEREAL_NVP(radiationOutput), CEREAL_NVP(isPlaced), CEREAL_NVP(isActive) /*Inventory has no serialize mechanism atm*/;
	}
};

#include <cereal/archives/xml.hpp>
//Register Production as a derived class
CEREAL_REGISTER_TYPE(Warehouse);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Warehouse, Structure);