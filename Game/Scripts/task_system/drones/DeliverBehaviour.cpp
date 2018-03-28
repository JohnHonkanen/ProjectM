#include "DeliverBehaviour.h"
#include "../../Structure.h"
v1::TaskSystem::DeliverBehaviour::DeliverBehaviour()
{
	clock.StartClock();
}

bool v1::TaskSystem::DeliverBehaviour::Run(double dt)
{
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

	
}
