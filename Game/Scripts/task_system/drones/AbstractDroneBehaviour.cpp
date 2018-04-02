#include "AbstractDroneBehaviour.h"
#include "DroneController.h"

namespace v1 {
	namespace TaskSystem
	{
		TaskInformation::TaskInformation()
		{
		}

		TaskInformation::TaskInformation(vec3 to, DroneController * controller) :to(to), controller(controller)
		{

		}

		TaskInformation::TaskInformation(const TaskInformation & task) : to(task.to), controller(task.controller)
		{
		}
	}
}

