#pragma once
#include "../Task.h"
#include <glm\glm.hpp>
class Drone;
namespace v1 {
	namespace TaskSystem {

		class DroneController
		{
		public:
			DroneController(class Drone *drone);
			void Update(double dt);
			bool AssignTask(Task t);
			void ForceTask(Task t);
		private:
			enum State
			{
				IDLE,
				ACTIVE,
				RECHARGE,
			};

			struct IdleBob {
				enum IDLE_STATE {
					UP,
					DOWN,
					NONE
				};
				IDLE_STATE state;
				float upper_elevation, lower_elevation;
				float bobSpeed;
			};
			
			void ApplyDroneBehaviour(double dt);
			void IdleBehaviour(double dt);
			void ActiveBehaviour(double dt);
			void RechargeBehaviour(double dt);

			State state;
			IdleBob idleBob;
			Task task;
			Drone *drone;

			float elevation_level;
		};
	}
}