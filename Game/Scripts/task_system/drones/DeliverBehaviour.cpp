#include "DeliverBehaviour.h"
#include "../Task.h"
#include "../../Structure.h"
#include "GoToBehaviour.h"
#include "../../Hub.h"

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

		boxObj->transform->SetPosition(drone->transform->GetPosition());
		
		Inventory * toInventory = &task.To()->GetInventory();
		ResourceName resource = task.GetResource();
		int amount = 200;
		int amountInDrone = drone->GetInventory().Contains(resource);

		if (amountInDrone < amount)
		{
			amount = amountInDrone;
		}
		drone->GetInventory().Remove(resource, amount);

		task.To()->Deposit(resource, amount);

		task.Fufill(amount);

		if (drone->GetInventory().Contains(resource) == 0 || toInventory->CheckStorageFull(resource) == 0)
		{
			boxObj->transform->SetPosition(vec3(0, -10, 0));
			//Check if Task is Completed
			int amountLeft = task.HasLeft();
			if (amountLeft > 0)
			{
				Task t = Task(TASK_TYPE::REQUEST, 20, task.From(), nullptr, task.GetResource(), amountLeft);
				info.controller->GetHub()->GetTaskManager()->AddTask(t, t.GetPriority());
			}
			return true;
		}

		clock.ResetClock();
	}

	if (boxObj != nullptr)
	{
		boxObj->transform->Translate(vec3(0, -10, 0) * float(dt / 1000.0f));
	}

	return false;
}
	


void v1::TaskSystem::DeliverBehaviour::Next()
{
	//If info is final set task to complete
	if (info.finalStep)
	{
		info.controller->SetState(nullptr);
		info.controller->GetTask().From()->TaskCompleted();
		info.controller->SetInternalStateIdle();
		info.controller->AssignTaskWithoutBehaviour(Task());
		delete this;
		return;
	}
}
