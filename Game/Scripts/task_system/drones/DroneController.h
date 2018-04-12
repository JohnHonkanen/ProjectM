#pragma once
#include "../Task.h"
#include <glm\glm.hpp>
#include "utility\Clock.h"
#include "core\GameObject.h"
class Drone;
class Hub;

namespace v1 {
	namespace TaskSystem {

		class DroneController
		{
		public:
			DroneController(Drone *drone, Hub * hub);
			void Start();
			void Update(double dt);
			/**Assigns the task and activate the GoTo behaviour to start the process*/
			bool AssignTask(Task t);
			/** Assigns a task without the GoTo behaviour call*/
			bool AssignTaskWithoutBehaviour(Task t);
			/** Force a task onto the drone, ignoring wheter or not it already has a task */
			void ForceTask(Task t);

			void SetState(class AbstractDroneBehaviour * state) { droneState = state; };

			Drone *GetDrone() {
				return drone;
			};

			Task GetTask() {
				return task;
			};

			float GetBaseSpeed() {
				return baseSpeed;
			};

			float GetSpeedMod() {
				return speedMod;
			}

			float GetCollectionRate()
			{
				return collectionRate;
			}

			Engine::GameObject * GetResourceBox();

			Hub * GetHub() {
				return hub;
			};

			enum State
			{
				IDLE,
				ACTIVE,
				RECHARGE,
			};

			void SetInternalState(State in_state) { state = in_state; };

			void SetInternalStateIdle() { state = IDLE; }

			void CancelTasks();
		private:
			Hub * hub;
			

			struct IdleBob {
				enum IDLE_STATE {
					UP,
					DOWN,
					NONE
				};
				IDLE_STATE state;
				float upperElevation, lowerElevation;
				float bobSpeed;
			};
			
			void ApplyDroneBehaviour(double dt);
			void IdleBehaviour(double dt);
			void ActiveBehaviour(double dt);
			void RechargeBehaviour(double dt);

			void CollectionRoutine(double dt);
			void DeliverRoutine(double dt);

			State state;
			IdleBob idleBob;
			Task task;
			Drone *drone;

			float elevationLevel;

			enum ACTIVE_STATE {
				COLLECT,
				MOVE,
				DELIVER,
				RISE,
				PARK,
				ACTIVE_IDLE,
				REQUEST
			};
			ACTIVE_STATE activeState;
			float baseSpeed = 40.0f;
			float speedMod = 1.0f;
			bool forceIdle = false;

			float collectionRate = 3.0f;
			bool collecting = false;
			Engine::Utility::Clock clock;

			class AbstractDroneBehaviour * droneState;

			Engine::GameObject box;
			Engine::GameObject * boxObj;
		};
	}
}