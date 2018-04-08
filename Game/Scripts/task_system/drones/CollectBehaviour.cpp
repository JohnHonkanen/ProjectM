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

		Structure * structure;
		int amount = task.GetAmount();
		if (task == TASK_TYPE::REQUEST)
		{
			structure = task.To();
		}
		else {
			structure = task.From();
		}
		ResourceName resource = task.GetResource();
		int spaceLeftInDrone = drone->GetInventory().CheckStorageFull(resource);

		if (spaceLeftInDrone < amount)
		{
			amount = spaceLeftInDrone;
			spaceLeftInDrone = 0;
		}

		int amountCollected = structure->Collect(resource, amount, task.GetIndex());

		drone->GetInventory().AddItem(resource, amountCollected);


		return true;
		

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

	if (task.GetType() == TASK_TYPE::COLLECT || task.GetType() == TASK_TYPE::REQUEST)
	{
		int x, y;
		task.From()->GetTilePosition(x, y);
		Structure * nearest = info.controller->GetHub()->FindNearestToDeposit(WAREHOUSE, x, y, task.GetResource());
		GoToBehaviour *state = new GoToBehaviour();
		state->info = info;
		if (task.GetType() == TASK_TYPE::COLLECT)
		{
			nearest = info.controller->GetHub()->FindNearestToDeposit(WAREHOUSE, x, y, task.GetResource());
		}
		else if(task.GetType() == TASK_TYPE::REQUEST)
		{
			nearest = task.From();
		}
		if (nearest == nullptr) //Not Found Anymore, Abandon ship
		{
			info.controller->AssignTask(task);
			info.controller->SetState(nullptr);
			info.controller->GetTask().From()->TaskCompleted(task.GetType(), task.GetIndex());
			//info.controller->GetTask().To()->DeRegisterDroneToStructure();
			info.controller->SetInternalStateIdle();
			info.controller->AssignTaskWithoutBehaviour(Task());
		}
		else {
			state->info.to = nearest->ParkingLocation();
			state->info.finalStep = true;

			task.SetTo(nearest);
			info.controller->AssignTaskWithoutBehaviour(task);
			info.controller->SetState(state);
		}
		
	}

	delete this;
}
