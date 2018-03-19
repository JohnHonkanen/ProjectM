#include "DroneController.h"
#include "../../Drone.h"
#include <glm\gtx\compatibility.hpp>
#include "../../Structure.h"
namespace v1{
	namespace TaskSystem
	{
		DroneController::DroneController(Drone *drone): drone(drone), elevationLevel(30.0f),
			idleBob({IdleBob::NONE, 2, 2, 5 }), state(IDLE), activeState(ACTIVE_IDLE)
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
			if (task.GetType() != TASK_TYPE::NONE)
			{
				state = ACTIVE;
			}

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
			float upperBounds = elevationLevel + idleBob.upperElevation;
			float lowerBounds = elevationLevel - idleBob.lowerElevation;

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
				if (position.y >= upperBounds)
				{
					idleBob.state = IdleBob::DOWN;
				}
			}
			else {
				if (position.y <= lowerBounds)
				{
					idleBob.state = IdleBob::UP;
				}
			}
			vec3 pos;
			switch (idleBob.state)
			{
			case IdleBob::UP:
				pos = lerp(position, vec3(position.x, upperBounds + 1, position.z), 0.02f);
				drone->transform->SetPosition(pos);
				break;
			case IdleBob::DOWN:
				pos = lerp(position, vec3(position.x, lowerBounds - 1, position.z), 0.01f);
				drone->transform->SetPosition(pos);
				break;
			default:
				break;
			}
		}
		void DroneController::ActiveBehaviour(double dt)
		{
			vec3 position = drone->transform->GetPosition();

			if (position.y < elevationLevel)
			{
				activeState = RISE;
			}
			else {
				activeState = MOVE;
			}

			//Rotate to face dir
			vec3 toPos = position;
			switch (task.GetType())
			{
			case TASK_TYPE::COLLECT:
				toPos = task.From()->gameObject->transform->GetPosition();
				break;
			default:
				break;
			}

			if (distance(position, toPos) < 0.5f)
			{
				activeState = PARK;
			}
			vec3 dir = normalize(toPos - position);
			float angle = atan2(dir.x, dir.z) + radians(90.0f);
			glm::quat curRot = drone->transform->GetQuaternion();
			glm::quat rot = quat(0, 1 * sin(angle / 2), 0, cos(angle / 2));
			quat inter_rot = lerp(curRot, rot, 0.1f);
			drone->transform->SetQuaternion(inter_rot);
			

			vec3 pos;
			switch (activeState)
			{
			case RISE:
				pos = lerp(position, vec3(position.x, elevationLevel + 1, position.z), 0.02f);
				drone->transform->SetPosition(pos);
				break;
			case MOVE:
				drone->transform->Translate(dir * (baseSpeed * speedMod) * float(dt / 1000.0f));
				break;
			case PARK:
				drone->transform->SetPosition(toPos);
				activeState = COLLECT;
				break;
			case COLLECT:
				CollectionRoutine();
				break;
			case DELIVER:
				DeliverRoutine();
				break;
			default:
				break;
			}

		}
		void DroneController::RechargeBehaviour(double dt)
		{
		}
		void DroneController::CollectionRoutine()
		{
		}
		void DroneController::DeliverRoutine()
		{
		}
	}
}

