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
	ResourceName producing;										//Resource building is producing
	ResourceName inputResource;									//Resource needed to create buildings output, found using recipe
	Engine::Utility::Clock clock;								//Clock for update triggers
	Hub * hub;													//Hub reference
	ResourceManager * resourceManager;							//Resource manager reference
	bool isProducing = false;									//Defines if an output has been set for a building
	BuildingProductionAnims* billboard;							//Billboarding reference, triggered on an items production
	v1::TaskSystem::Task request;								//

	v2::Inventory inventoryOutput;								//Second inventory for factory where buildings require an input

	void DomeProduction();										//
	void FactoryProduction();									//

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

	void Start();												//Starts clock and sets alarm
	void OnLoad();
	void Update(double currentTime);							//calls production metod and generates building tasks

	void SetProduction(ResourceName type);						//Sets building production, and empties onventory if production type in changed
	void SetActive(bool change);								//Sets if building is active, and when not active also sets it to not be producing a resource
	ResourceName GetProduction() { return producing; }			//Returns resource building is producing

	Resources* GetResource() { return resourceManager->Find(producing); }

	bool GetProducing() { return isProducing; }

	int Collect(ResourceName resource, int amount, int index);				//Calls structure collect method if building is a dome, or uses local collect if building is a factory
	int GetInputCount();										//Returns a factory's ingredient amount
	int GetOutputCount();										//Returns output inventory's amount
	void TaskCompleted(TASK_TYPE type, int index);							//
	void IncreaseLevel();										//Increases a buildings productivity and upkeep
	void DecreaseLevel();										//reduces a buildings productivity and upkeep
	int GetUpkeep();
	void IncreaseTaskNumber(TASK_TYPE type, int index);

	int GetUpkeep(); //@Override
	BuildingProductionAnims* GetBillboard() const { return billboard; }

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


