#include "GoToBehaviour.h"
#include "DroneController.h"
#include "../../Drone.h"
#include "../Task.h"
#include "CollectBehaviour.h"
#include "DeliverBehaviour.h"
namespace v1
{
	namespace TaskSystem {

		bool GoToBehaviour::Run(double dt)
		{
			Drone *drone = info.controller->GetDrone();
			Task task = info.controller->GetTask();
			vec3 position = drone->transform->GetPosition();
			float baseSpeed = info.controller->GetBaseSpeed();
			float speedMod = info.controller->GetSpeedMod();
			position.y = 0;
			

			//Determmine Destination
			vec3 destination = info.to;

			destination.y = 0;

			//Check if We have reached target
			if (distance(position, destination) < 0.5f)
			{
				//Target Reached
				return true;
			}

			//Move to Target
			//Rotate our drone to orient destination
			vec3 dir = normalize(destination - position);
			float angle = atan2(dir.x, dir.z);
			vec3 droneAngle = drone->transform->GetRotation();
			droneAngle.y = degrees(angle) - 90.0f;
			drone->transform->SetEulerAngle(droneAngle);

			//Move to Target
			drone->transform->Translate(dir * (baseSpeed * speedMod) * float(dt / 1000.0f)); 
			
			return false;
		}

		void GoToBehaviour::Next()
		{
			Task task = info.controller->GetTask();

			if (task.GetType() == TASK_TYPE::COLLECT)
			{
				AbstractDroneBehaviour * state;
				if (!info.finalStep)
				{
					state = new CollectBehaviour();
					
				}
				else {
					state = new DeliverBehaviour();
				}
				
				state->info = info;
				info.controller->SetState(state);
			}

			delete this;
		}

	}
}
