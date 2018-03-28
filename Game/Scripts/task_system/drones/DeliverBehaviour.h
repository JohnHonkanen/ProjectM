#pragma once
#include "AbstractDroneBehaviour.h"
#include "utility\Clock.h"
namespace v1 {
	namespace TaskSystem {
		class DeliverBehaviour : public AbstractDroneBehaviour
		{
		public:
			DeliverBehaviour();
			bool Run(double dt);
			void Next();

		private:
			Engine::Utility::Clock clock;
		};
	}
}