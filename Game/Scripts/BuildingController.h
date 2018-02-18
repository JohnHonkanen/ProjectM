#pragma once
#include "components\Behaviour.h"
#include "BuildingManager.h"
#include "TerrainCollisionHelper.h"
#include <string>
class BuildingController : public Behaviour
{
public:
	~BuildingController();
	static BuildingController* Create(GameObject * gameObject, BuildingManager * buildingManager);
	void Copy(GameObject *copyObject);
	void SetObjectToBuild(std::string structure);

	void Start();
	void Update(double dt);

	//To Be Removed
	void AddTempObject(GameObject *object);
	//Our Collision Helper to check our point in grid
	TerrainCollisionHelper colHelper;
private:
	BuildingManager * buildingManager;
	GameObject * objectToBuild;
	bool showGameObject;
};