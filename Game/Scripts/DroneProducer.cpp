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
	return;
	int x, y;
	structure->GetTilePosition(x, y);
	Structure *nearest = hub->FindNearest(StructureType::WAREHOUSE, x, y);

	if (nearest == nullptr)
		return;

}
