#pragma once
#include "components\Behaviour.h"
#include "BuildingManager.h"
#include "TerrainCollisionHelper.h"
#include <string>
class BuildingController : public Behaviour
{
public:
	~BuildingController();
	static BuildingController* Create(GameObject * gameObject, BuildingManager * buildingManager, class Hub *hub);
	void Copy(GameObject *copyObject);
	void SetObjectToBuild(std::string structure);

	void Start();
	void Update(double dt);

	void SetBuildMode(bool mode);
	void SetMouseHeld(bool state);
	//To Be Removed
	void AddTempObject(GameObject *object);
	//Our Collision Helper to check our point in grid
	TerrainCollisionHelper colHelper;
private:
	class Hub * hub;
	BuildingManager * buildingManager;
	GameObject * objectToBuild;
	std::string structureName;
	bool ghostInstantiated;
	bool buildMode = false;
	bool mouseHeld = false;
};