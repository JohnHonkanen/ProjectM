#include "RequestBehaviour.h"
#include "../Task.h"
#include "../../Structure.h"
#include "GoToBehaviour.h"
#include "../../Hub.h"

v1::TaskSystem::RequestBehaviour::RequestBehaviour()
{
	clock.StartClock();
}

bool v1::TaskSystem::RequestBehaviour::Run(double dt)
{
	

	return false;
}

void v1::TaskSystem::RequestBehaviour::Next()
{
	Task task = info.controller->GetTask();

	if (task.GetType() == TASK_TYPE::REQUEST)
	{
		int x, y;
		task.From()->GetTilePosition(x, y);
		Structure * nearest = info.controller->GetHub()->FindNearestWithResource(WAREHOUSE, x, y, task.GetResource());
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
