/*
Production Class - Used for maintaing any building type that produces resources.

Devs: Jack Smith (B00308927) & Greg Smith (B00308929)
*/

#include "Production.h"

using namespace std;

Production::Production() {

}

Production::~Production()
{
}

Production::Production(string name, int hp, int pow, int eff, int radOut, bool placed, bool active)
{
	this->name = name;
	this->health = hp;
	this->powerUsage = pow;
	this->productionEfficiency = eff;
	this->radiationOutput = radOut;
	this->isPlaced = placed;
	this->isActive = active;
}

Production * Production::Create(string name, int hp, int pow, int eff, int rad, bool placed, bool active)
{
	Production *p= new Production(name, hp, pow, eff, rad, placed, active);
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

void Production::update(int eff, bool act)
{
	if (act && inv->InventorySize() < 100) {
		setStorage(getStorage() + 1 * eff);
	}
}



