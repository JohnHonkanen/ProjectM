#pragma once
#include "AbstractDroneBehaviour.h"
#include "utility\Clock.h"
namespace v1 {
	namespace TaskSystem {
		class RequestBehaviour : public AbstractDroneBehaviour
		{
		public:
			RequestBehaviour();
			bool Run(double dt);
			void Next();

		private:
			Engine::Utility::Clock clock;
		};
	}
}
