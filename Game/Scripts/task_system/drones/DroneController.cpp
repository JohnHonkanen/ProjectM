#include "DroneController.h"
#include "../../Drone.h"
namespace v1{
	namespace TaskSystem
	{
		DroneController::DroneController(Drone *drone): drone(drone), elevation_level(30.0f),
			idleBob({IdleBob::NONE, 5, 5, 5 }), state(IDLE)
		{
		}
		void DroneController::Update(double dt)
		{
			ApplyDroneBehaviour(dt);
		}
		bool DroneController::AssignTask(Task t)
		{
			if (state == IDLE)
			{
				state = ACTIVE;
				task = t;
				return true;
			}

			//Has an active task
			return false;
		}
		void DroneController::ForceTask(Task t)
		{
			state = ACTIVE;
			task = t;
		}

		void DroneController::ApplyDroneBehaviour(double dt)
		{
			switch (state)
			{
			case IDLE:
				IdleBehaviour(dt);
				break;
			case ACTIVE:
				ActiveBehaviour(dt);
				break;
			case RECHARGE:
				RechargeBehaviour(dt);
				break;
			default:
				break;
			}
		}
		void DroneController::IdleBehaviour(double dt)
		{
			vec3 position = drone->transform->GetPosition();
			float upperBounds = elevation_level + idleBob.upper_elevation;
			float lowerBounds = elevation_level - idleBob.lower_elevation;

			if (idleBob.state == IdleBob::NONE)
			{
				if (position.y < upperBounds)
				{
					idleBob.state = IdleBob::UP;
				}
				else {
					idleBob.state = IdleBob::DOWN;
				}
			}

			if (idleBob.state == IdleBob::UP)
			{
				if (position.y > upperBounds)
				{
					idleBob.state = IdleBob::DOWN;
				}
			}
			else {
				if (position.y < lowerBounds)
				{
					idleBob.state = IdleBob::UP;
				}
			}

			switch (idleBob.state)
			{
			case IdleBob::UP:
				drone->transform->Translate(vec3(0, idleBob.bobSpeed * dt/1000.0f, 0));
				break;
			case IdleBob::DOWN:
				drone->transform->Translate(vec3(0, -idleBob.bobSpeed * dt/1000.0f, 0));
				break;
			default:
				break;
			}
		}
		void DroneController::ActiveBehaviour(double dt)
		{
		}
		void DroneController::RechargeBehaviour(double dt)
		{
		}
	}
}

