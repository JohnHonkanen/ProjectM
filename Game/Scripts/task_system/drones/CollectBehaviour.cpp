#include "CollectBehaviour.h"
#include "../Task.h"
#include "../../Structure.h"
#include "GoToBehaviour.h"
#include "../../Hub.h"

v1::TaskSystem::CollectBehaviour::CollectBehaviour()
{
	clock.StartClock();
}

bool v1::TaskSystem::CollectBehaviour::Run(double dt)
{
	clock.UpdateClock();
	clock.SetDelay(info.controller->GetCollectionRate() * 1000);

	GameObject *boxObj = info.controller->GetResourceBox();

	if (clock.Alarm())
	{
		Task task = info.controller->GetTask();
		Drone *drone = info.controller->GetDrone();

		boxObj->transform->SetPosition(drone->transform->GetPosition() - vec3(0, drone->transform->GetPosition().y, 0));

		Inventory * fromInventory = &task.From()->GetInventory();
		ResourceName resource = task.GetResource();
		int amount = 200;
		int left = drone->GetInventory().AddItem(resource, amount);
		int toRemove = amount - left;
		fromInventory->Remove(resource, toRemove);

		if (fromInventory->Contains(resource) == 0 || drone->GetInventory().CheckStorageFull(resource) == 0)
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

void v1::TaskSystem::CollectBehaviour::Next()
{
	Task task = info.controller->GetTask();

	if (task.GetType() == TASK_TYPE::COLLECT)
	{
		int x, y;
		task.From()->GetTilePosition(x, y);
		Structure * nearest = info.controller->GetHub()->FindNearestToDeposit(WAREHOUSE, x, y, task.GetResource());
		GoToBehaviour *state = new GoToBehaviour();
		state->info = info;
		state->info.to = nearest->transform->GetPosition();
		state->info.finalStep = true;
		task.SetTo(nearest);
		info.controller->AssignTaskWithoutBehaviour(task);

		info.controller->SetState(state);
	}

	delete this;
}
