#pragma once
#include "AbstractDroneBehaviour.h"

namespace v1 {
	namespace TaskSystem {
		class GoToBehaviour : public AbstractDroneBehaviour
		{
		public:
			bool Run(double dt);
			void Next();
		};
	}
}