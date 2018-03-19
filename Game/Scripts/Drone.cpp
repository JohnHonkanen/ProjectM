#include "Drone.h"
#include "core\GameObject.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\quaternion.hpp>
#include "core\GameEngine.h"
Drone * Drone::Create(GameObject * gameObject)
{
	Drone *d = new Drone();
	gameObject->AddComponent(d);

	return d;
}

void Drone::Copy(GameObject * copyObject)
{
	Drone *d = new Drone();
	d->destination = destination;
	copyObject->AddComponent(d);
}

void Drone::Start()
{
	//Default values
	speed = 100.0f;
	verticalSpeed = 30.0f;
	minY = 50.0f;
	liftOff = false;
}

void Drone::Update(double dt)
{
	controller.Update(dt);
}

void Drone::SetDestination(vec3 destination)
{
	Drone::destination = destination;
}

v2::Inventory & Drone::GetInventory()
{
	return inventory;
}
