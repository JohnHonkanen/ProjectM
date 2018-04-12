#pragma once
#include "components\Behaviour.h"
#include "utility\Clock.h"

class DroneProducer : public Behaviour
{
public:
	static DroneProducer * Create(GameObject *gameObject, class Hub* hub, class Structure *structure);
	void Copy(GameObject* gameObject);
	void Update(double dt);
	/** Create a drone*/
	void SpawnDrone();
private:
	Engine::Utility::Clock timer;
	class Structure *structure;
	class Hub* hub;
};