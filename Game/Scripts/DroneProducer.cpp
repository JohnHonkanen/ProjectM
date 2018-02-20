#include "DroneProducer.h"
#include "Hub.h"
#include "core\GameObject.h"
#include "Structure.h"
#include "components\MeshRenderer.h"
#include "Drone.h"
#include "core\GameEngine.h"
#include "Structure.h"
DroneProducer * DroneProducer::Create(GameObject * gameObject, Hub * hub, Structure *structure)
{
	DroneProducer  * dp = new DroneProducer();
	dp->hub = hub;
	dp->structure = structure;
	dp->timer.SetDelay(1000);
	dp->timer.StartClock();
	

	gameObject->AddComponent(dp);

	return dp;
}

void DroneProducer::Copy(GameObject * gameObject)
{
}

void DroneProducer::Update(double dt)
{
	timer.UpdateClock();
	if (timer.Alarm())
	{
		timer.ResetClock();
		timer.SetDelay(rand() % 3000 + 1000);
		SpawnDrone();
	}
}

void DroneProducer::SpawnDrone()
{
	int x, y;
	structure->GetTilePosition(x, y);
	Structure *nearest = hub->FindNearest(StructureType::WAREHOUSE, x, y);

	if (nearest == nullptr)
		return;

	//Drone Code
	GameObject *droneObject = new GameObject("drone");
	MeshRenderer::Create(droneObject, "Game/Assets/Models/mobajuice/Drone.DAE");
	Drone *drone = Drone::Create(droneObject);
	drone->SetDestination(nearest->transform->GetPosition());
	droneObject->material->diffuseMap = "Game/Assets/Textures/building_placeholder.jpg";
	droneObject->transform->Scale(vec3(1.5));
	droneObject->transform->SetPosition(transform->GetPosition());

	droneObject->Instantiate();

	delete droneObject;
}
