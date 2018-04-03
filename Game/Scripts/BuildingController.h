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

	bool GetBuildMode();
	void SetBuildMode(bool mode);
	void SetMouseHeld(bool state);
	//To Be Removed
	void AddTempObject(GameObject *object);

	class PlayerActions *GetPlayerAction();
	//Our Collision Helper to check our point in grid
	TerrainCollisionHelper colHelper;

	bool IsInDebt();  // Gets player debt status from player economy.
private:
	Structure * FindStructure(float x, float y, float width);
	void RegisterToNetwork(Structure * s, float x, float y, float width);
	class Hub * hub;
	class PlayerActions *playerAction;
	BuildingManager * buildingManager;
	GameObject * objectToBuild;
	std::string structureName;
	bool ghostInstantiated;
	bool buildMode = false;
	bool mouseHeld = false;
};