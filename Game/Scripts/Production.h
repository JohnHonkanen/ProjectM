/*
Production Class - Used for maintaing any building type that produces resources.

Dev: Greg Smith (B00308929)
*/

#pragma once
#include "BuildingProductionAnims.h"
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
#include "utility\Clock.h"
#include "Hub.h"
#include "task_system\Task.h"


using namespace std;
using namespace glm;

class Production : public Structure {
private:
	ResourceName producing;
	ResourceName inputResource;
	Engine::Utility::Clock clock;
	Hub * hub;
	ResourceManager * resourceManager;
	bool isProducing = false;
	BuildingProductionAnims* billboard;
	v1::TaskSystem::Task request;

	v2::Inventory inventoryOutput;

	void DomeProduction();
	void FactoryProduction();

	int numCollectTask = 0;
	int maxCollectTask = 1;

	int numRequestTask = 0;
	int maxRequestTask = 1;

public:

	Production();
	~Production();
	Production(string name, StructureType typ,int hp, int pow, int eff, int up, int radOut, bool placed, bool active, ResourceManager * resourceMan, Hub * hub);
	static Production * Create(string name, StructureType typ, int hp, int pow, int eff,int up, int cost, int rad, bool placed, bool active, ResourceManager * resourceMan, Hub * hub);

	void Copy(GameObject *copyObject);

	void Start();
	void OnLoad();
	void Update(double currentTime);

	void SetProduction(ResourceName type);
	void SetActive(bool change);
	ResourceName GetProduction() { return producing; }

	Resources* GetResource() { return resourceManager->Find(producing); }

	bool GetProducing() { return isProducing; }

	int Collect(ResourceName resource, int amount, int index);
	int GetInputCount();
	int GetOutputCount();
	void TaskCompleted(TASK_TYPE type, int index);
	void IncreaseLevel();
	void DecreaseLevel();

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


