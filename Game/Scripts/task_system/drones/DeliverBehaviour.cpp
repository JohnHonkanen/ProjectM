#include "DeliverBehaviour.h"
#include "../Task.h"
#include "../../Structure.h"
#include "GoToBehaviour.h"
#include "../../Hub.h"
#include "../../Drone.h"

v1::TaskSystem::DeliverBehaviour::DeliverBehaviour()
{
	clock.StartClock();
}

bool v1::TaskSystem::DeliverBehaviour::Run(double dt)
{
	clock.UpdateClock();
	clock.SetDelay(info.controller->GetCollectionRate() * 1000);

	GameObject *boxObj = info.controller->GetResourceBox();

	if (clock.Alarm())
	{
		Task task = info.controller->GetTask();
		Drone *drone = info.controller->GetDrone();

		int x, y;
		task.From()->GetTilePosition(x, y);
		boxObj->transform->SetPosition(drone->transform->GetPosition() - vec3(0, y, 0));
		
		Inventory * toInventory = &task.To()->GetInventory();
		ResourceName resource = task.GetResource();
		int amount = 200;
		int left = drone->GetInventory().Remove(resource, amount);
		int toAdd = amount - left;
		toInventory->AddItem(resource, toAdd);

		if (drone->GetInventory().Contains(resource) == 0 || toInventory->CheckStorageFull(resource) == 0)
		{
			return true;
		}

		clock.ResetClock();
	}

	if (boxObj != nullptr)
	{
		boxObj->transform->Translate(vec3(0, 10, 0) * float(dt / 1000.0f));
	}



	return false;
}
	


void v1::TaskSystem::DeliverBehaviour::Next()
{
	//If info is final set task to complete
	if (info.finalStep)
	{
		info.controller->AssignTaskWithoutBehaviour(Task());
		info.controller->SetState(nullptr);
		info.controller->GetTask().From()->TaskCompleted();
		delete this;
		return;
	}

	delete this;
}
