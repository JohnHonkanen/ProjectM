#pragma once
#include "components\Behaviour.h"
#include <glm\glm.hpp>
#include "InventoryV2.h"
#include "task_system\drones\DroneController.h"

class Drone : public Behaviour
{
public:
	Drone();
	static Drone *Create(GameObject *gameObject);
	void Copy(GameObject *copyObject);

	void Start();
	void Update(double dt);

	void SetDestination(vec3 destination);
	v2::Inventory &GetInventory();
	v1::TaskSystem::DroneController const &GetController();
private:
	float speed;
	float verticalSpeed;
	float acceleration;
	glm::vec3 destination;
	float minY;
	bool reachedDestination;
	bool liftOff;

	v2::Inventory inventory;
	v1::TaskSystem::DroneController controller;

};