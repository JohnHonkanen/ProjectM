#pragma once
#include "core\Transform.h"
#include"..\..\Drone.h"
namespace v1 {
	namespace TaskSystem
	{
		struct TaskInformation {
			TaskInformation();
			TaskInformation(vec3 to, class DroneController *controller);
			TaskInformation(const TaskInformation& task);
			vec3 to;
			bool finalStep = false;

			class DroneController *controller;
		};

		class AbstractDroneBehaviour
		{
		public:
			virtual bool Run(double dt) = 0;
			virtual void Next() = 0;

			TaskInformation info;
		};
	}
}
