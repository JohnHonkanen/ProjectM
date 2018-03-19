#pragma once
#include "../Task.h"
namespace v1 {
	namespace TaskSystem {

		class DroneController
		{
		public:
			DroneController();
			void Update(double dt);
			bool AssignTask(Task t);
			void ForceTask(Task t);
		private:
			void ApplyDroneBehaviour(double dt);
			Task task;
		};
	}
}
