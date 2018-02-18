#pragma once
#include "components\Behaviour.h"
#include "BuildingManager.h"
#include "ResourceManager.h"
class GameManager : public Behaviour
{
public:
	static GameManager* Create(GameObject * gameObject);
	void Copy(GameObject *copyObject);

	BuildingManager buildingManager;
	ResourceManager resourceManager;

	
};