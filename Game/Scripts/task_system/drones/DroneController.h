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
			bool AssignTask(Task t);
			void ForceTask(Task t);

		private:
			Hub * hub;
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
				ACTIVE_IDLE
			};
			ACTIVE_STATE activeState;
			float baseSpeed = 20.0f;
			float speedMod = 1.0f;
			bool forceIdle = false;

			float collectionRate = 3.0f;
			bool collecting = false;
			Engine::Utility::Clock clock;

			Engine::GameObject box;
			Engine::GameObject * boxObj;
		};
	}
}