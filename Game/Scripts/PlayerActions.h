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
private:
	std::string selectedTexture;
	std::string buildingTexture;

	class BuildingController *buldingController;
	class Hub *hub;
	class Structure *selectedStructure;
};