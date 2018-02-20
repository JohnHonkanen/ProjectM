#pragma once
#include "components\Behaviour.h"

class PlayerActions : public Behaviour
{
public:
	static PlayerActions * Create(GameObject* gameObject, class BuildingController* bController, class Hub * hub);
	void Copy(GameObject *copyObject);

	void Start();
	void Update(double dt);
private:
	class BuildingController *buldingController;
	class Hub *hub;
};