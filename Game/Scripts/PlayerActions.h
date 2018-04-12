#pragma once
#include "components\Behaviour.h"
#include <string>
class PlayerActions : public Behaviour
{
public:
	static PlayerActions * Create(GameObject* gameObject, class BuildingController* bController, class Hub * hub);
	void Copy(GameObject *copyObject);

	void Start();
	void Update(double dt);
	class Structure * GetSelectedStructure();
	// Sets the selection status of the structure to nullptr
	// This will cause it to be deselected
	Structure * SetSelectedStructureNull() { return selectedStructure = nullptr; }
	/** Set to check if we are current in build mode in BuildingController */
	void SetBuildingStatus(bool status) { building = status; }
	/** Get BuildingStatus */
	bool GetBuildingStatus() const{ return building; }
private:
	std::string selectedTexture;
	std::string buildingTexture;

	class BuildingController *buldingController;
	class Hub *hub;
	class Structure *selectedStructure;
	bool building = false;
};