#include "DroneController.h"
#include "../../Drone.h"
#include <glm\gtx\compatibility.hpp>
#include <glm\gtc\quaternion.hpp>
#include "../../Structure.h"
#include "../../Hub.h"
#include "../TaskManager.h"
#include "components\MeshRenderer.h"
#include "AbstractDroneBehaviour.h"
#include "GoToBehaviour.h"


namespace v1{
	namespace TaskSystem
	{
		DroneController::DroneController(Drone *drone, Hub * hub): drone(drone), elevationLevel(30.0f),
			idleBob({IdleBob::NONE, 2, 2, 5 }), state(IDLE), activeState(ACTIVE_IDLE), hub(hub)
		{
			clock.SetDelay(collectionRate * 1000);
			clock.StartClock();
		}
		void DroneController::Start()
		{
			MeshRenderer::Create(&box, "Game/Assets/Models/cube/cube.obj");
			box.material->diffuseMap = "Game/Assets/Textures/building_selected.jpg";
		}
		void DroneController::Update(double dt)
		{
			clock.UpdateClock();
			ApplyDroneBehaviour(dt);
		}
		bool DroneController::AssignTask(Task t)
		{
			if (state == IDLE)
			{
				state = ACTIVE;
				task = t;
				if (droneState != nullptr)
				{
					delete droneState;
				}

				droneState = new GoToBehaviour();
				if (task.GetType() == TASK_TYPE::REQUEST) 
				{
					int x, y;
					task.From()->GetTilePosition(x, y);
					task.SetTo(GetHub()->FindNearestWithResource(WAREHOUSE, x,y,task.GetResource()));
				}

				//Did not find task
				if (task.To() == nullptr)
				{
					state = IDLE;

					auto taskManager = hub->GetTaskManager();
					if (taskManager->HasTask())
					{
						Task temp = task;
						AssignTask(taskManager->Pop()); //Recursion
						taskManager->AddTask(temp, temp.GetPriority());
					}

					if (task == TASK_TYPE::NONE)
					{
						return false;
					}

					if (task.To() == nullptr) {
						taskManager->AddTask(task, task.GetPriority());
						task = Task();
						
						return false;
					}
				}
				task.From()->RegisterDroneToStructure(this);
				if (task == TASK_TYPE::REQUEST)
				{
					task.To()->RegisterDroneToStructure(this);
				}
				droneState->info = TaskInformation(task.To()->ParkingLocation(), this);
				return true;
			}
			//Has an active task
			return false;
		}
		bool DroneController::AssignTaskWithoutBehaviour(Task t)
		{
			task = t;
			return true;
		}
		void DroneController::ForceTask(Task t)
		{
			state = ACTIVE;
			task = t;
		}
		GameObject * DroneController::GetResourceBox()
		{
			if (boxObj == nullptr)
			{
				boxObj = box.Instantiate();
				boxObj->transform->SetPosition(vec3(-9999));
			}

			return boxObj;
		}

		void DroneController::CancelTasks()
		{
			SetState(nullptr);
			GetTask().From()->TaskCompleted(task.GetType(), task.GetIndex());
			GetTask().From()->DeRegisterDroneToStructure(this);
			GetTask().To()->DeRegisterDroneToStructure(this);
			SetInternalStateIdle();
			AssignTaskWithoutBehaviour(v1::TaskSystem::Task());
		}

		void DroneController::ApplyDroneBehaviour(double dt)
		{
			if (task.GetType() != TASK_TYPE::NONE && !forceIdle)
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
			auto taskManager = hub->GetTaskManager();

			if (taskManager->HasTask())
			{
				AssignTask(taskManager->Pop());
			}

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
			if (droneState == nullptr)
			{
				IdleBehaviour(dt);
				return;
			}

			vec3 position = drone->transform->GetPosition();
			if (position.y < elevationLevel)
			{
				vec3 pos = lerp(position, vec3(position.x, elevationLevel + 1, position.z), 0.02f);
				drone->transform->SetPosition(pos);
				return;
			}

			//If Run is completed move to next state;
			if(droneState->Run(dt)) {
				droneState->Next();
			}
		}
		void DroneController::RechargeBehaviour(double dt)
		{
		}
		void DroneController::CollectionRoutine(double dt)
		{
			if (collecting == false)
			{
				collecting = true;
				clock.ResetClock();
			}
			if (clock.Alarm())
			{
				if (boxObj == nullptr)
				{
					boxObj = box.Instantiate();
				}
				boxObj->transform->SetPosition(drone->transform->GetPosition() - vec3(0, elevationLevel, 0));
				if (task.GetType() == TASK_TYPE::COLLECT)
				{
					Inventory * fromInventory = &task.From()->GetInventory();
					ResourceName resource = task.GetResource();
					int amount = 200;
					int left = drone->GetInventory().AddItem(resource, amount);
					int toRemove = amount - left;
					fromInventory->Remove(resource, toRemove);
					if (fromInventory->Contains(resource) == 0 || drone->GetInventory().CheckStorageFull(resource) == 0)
					{
						activeState = DELIVER;
						collecting = false;
					}
				}
				clock.ResetClock();
			}
			if (boxObj != nullptr)
			{
				boxObj->transform->Translate(vec3(0, 10, 0) * float(dt / 1000.0f));
			}
		}
		void DroneController::DeliverRoutine(double dt)
		{
			int x, y;
			Structure * nearest = new Structure();
			if (task.GetType() == TASK_TYPE::REQUEST)
			{
				task.From()->GetTilePosition(x, y);
				nearest = hub->FindNearestWithResource(WAREHOUSE, x, y, task.GetResource());
			}
			else if (task.GetType() == TASK_TYPE::COLLECT)
			{
				task.From()->GetTilePosition(x, y);
				nearest = hub->FindNearestToDeposit(WAREHOUSE, x, y, task.GetResource());
			}
			if (nearest == nullptr)
			{
				IdleBehaviour(dt);
				forceIdle = true;
				return;
			}

			forceIdle = false;

			vec3 position = drone->transform->GetPosition();
			vec3 to = nearest->transform->GetPosition();
			to.y = elevationLevel;

			if (distance(position, to) < 0.5f)
			{
				if (collecting == false)
				{
					collecting = true;
					clock.ResetClock();
				}
				if (drone->GetInventory().At(0).quantity == 0)
				{
					state = IDLE;
					activeState = ACTIVE_IDLE;
					task.From()->TaskCompleted(task.GetType(), task.GetIndex());
					//task.From()->DeRegisterDroneToStructure();
					task = Task();
					boxObj->transform->SetPosition(vec3(0, -10, 0));
					collecting = false;
				}
				else {

					if (clock.Alarm())
					{
						Inventory * wI = &nearest->GetInventory();
						drone->GetInventory().Send(wI, task.GetResource(), 200);
						boxObj->transform->SetPosition(drone->transform->GetPosition());
						clock.ResetClock();
					}

					if (boxObj != nullptr)
					{
						boxObj->transform->Translate(vec3(0, -10, 0) * float(dt / 1000.0f));
					}
				}
			}
			else {
				vec3 dir = normalize(to - position);
				float angle = atan2(dir.x, dir.z);
				vec3 droneAngle = drone->transform->GetRotation();
				droneAngle.y = degrees(angle) - 90.0f;
				drone->transform->SetEulerAngle(droneAngle);
				drone->transform->Translate(dir * (baseSpeed * speedMod) * float(dt / 1000.0f));
			}
		}
	}
}

