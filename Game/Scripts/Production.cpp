#include "Production.h"

using namespace std;

//serialization code please - X

Production::Production() {

}

Production::~Production()
{
}

Production::Production(string buildingName, int hp, int pow, int eff, int radOut, vec3 position, bool placed, bool active)
{
	name = buildingName;
	health = hp;
	powerUsage = pow;
	productionEfficiency = eff;
	radiationOutput = radOut;
	pos = position;
	isPlaced = placed;
	isActive = active;
}

Production * Production::Create(string name, int hp, int pow, int eff, int rad, vec3 position, bool placed, bool active)
{
	Production *p= new Production(name, hp, pow, eff, rad, position, placed, active);
	return p;
}

void Production::Copy(GameObject * copyObject)
{
	
	Production * copy = new Production();
	copy->name = Production::name;
	copy->health = Production::health;
	copy->powerUsage = Production::powerUsage;
	copy->productionEfficiency = Production::productionEfficiency;
	copy->radiationOutput = Production::radiationOutput;
	copy->pos = Production::pos;
	copy->isPlaced = Production::isPlaced;
	copy->isActive = Production::isActive;

	copyObject->AddComponent(copy);

	
}

void Production::OnLoad()
{
}

void Production::Update()
{
}

void Production::setProduction(string type, int eff, bool act)
{
	if (type == "dome") {
		domeProduction(eff, act);
	}
	else if (type == "factory") {
		factoryProduction(eff, act);
	}
}

//move production types into create method
void Production::domeProduction(int eff, bool act)
{
	//Limits production types of building
	//based on its type
	//To be loaded in from xml
}

void Production::factoryProduction(int eff, bool act)
{
	//Limits production types of building
	//based on its type
	//To be loaded in from xml
}

//void Production::update(int eff, bool act)
//{
//	if (act && storage.size() < 100) {
//		setStorage(getStorage() + 1 * eff);
//	}
//}



