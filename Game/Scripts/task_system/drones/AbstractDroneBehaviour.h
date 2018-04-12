#pragma once
#include "core\Transform.h"
#include"..\..\Drone.h"
namespace v1 {
	namespace TaskSystem
	{
		//Task information to be used by the drone behaviours
		struct TaskInformation {
			TaskInformation();
			TaskInformation(vec3 to, class DroneController *controller);
			TaskInformation(const TaskInformation& task);
			vec3 to;
			bool finalStep = false;

			class DroneController *controller;
		};
		/*Abstract Drone behaviour class to base drone behaviour on*/
		class AbstractDroneBehaviour
		{
		public:
			/** Run the behaviour */
			virtual bool Run(double dt) = 0;
			/** GoTo next behaviour */
			virtual void Next() = 0;

			TaskInformation info;
		};
	}
}
