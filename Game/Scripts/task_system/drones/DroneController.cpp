#include "DroneController.h"

namespace v1{
	namespace TaskSystem
	{
		DroneController::DroneController()
		{
			task = Task(); //Create Empty Task
		}
		void DroneController::Update(double dt)
		{
			ApplyDroneBehaviour(dt);
		}
		bool DroneController::AssignTask(Task t)
		{
			if (task.GetType() == TASK_TYPE::NONE)
			{
				task = t;
				return true;
			}

			//Has an active task
			return false;
		}
		void DroneController::ForceTask(Task t)
		{
			task = t;
		}

		void DroneController::ApplyDroneBehaviour(double dt)
		{
		}
	}
}

