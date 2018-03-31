#include "Drone.h"
#include "core\GameObject.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\quaternion.hpp>
#include "core\GameEngine.h"
#include "components\MeshRenderer.h"
#include "Hub.h"
Drone::Drone(Hub * hub) : controller(this, hub), inventory(1), hub(hub)
{
}

Drone * Drone::Create(GameObject * gameObject, Hub * hub, ResourceManager * resourceManager)
{
	Drone *d = new Drone(hub);
	d->resourceManager = resourceManager;
	d->inventory.SetResourceManager(resourceManager);
	gameObject->AddComponent(d);
	MeshRenderer::Create(gameObject, "Game/Assets/Models/mobajuice/SpaceShipDetailed.obj");
	gameObject->material->diffuseMap = "Game/Assets/Textures/building_placeholder.jpg";
	gameObject->transform->Scale(vec3(3));
	gameObject->transform->SetPosition(vec3(0));


	return d;
}

void Drone::Copy(GameObject * copyObject)
{
	Drone *d = new Drone(hub);
	d->resourceManager = resourceManager;
	d->inventory.SetResourceManager(resourceManager);
	copyObject->AddComponent(d);
}

void Drone::Start()
{
	//Default values
	speed = 100.0f;
	verticalSpeed = 30.0f;
	minY = 50.0f;
	liftOff = false;

	controller.Start();
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

v1::TaskSystem::DroneController const & Drone::GetController()
{
	return controller;
}
