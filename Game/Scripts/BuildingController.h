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

	/** Check to see if the player is current building something*/
	bool GetBuildMode();
	/** Manually change the build mode to another mode */
	void SetBuildMode(bool mode);
	/** Manually change the mouse held to another state */
	void SetMouseHeld(bool state);

	/** Get the Player Actions class */
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