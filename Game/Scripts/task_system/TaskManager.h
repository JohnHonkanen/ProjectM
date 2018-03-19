#pragma once
#include "components\Behaviour.h"
#include <queue>
#include <memory>

#include "Task.h"
namespace v1
{
	namespace TaskSystem
	{
		using TaskQueue = std::priority_queue<std::unique_ptr<Task>>;

		class TaskManager : public Behaviour
		{
		public:
			static TaskManager * Create(GameObject * gameObject);
			void Copy(GameObject * object);
			//Adds a Task to the task queue
			void AddTask(Task::TYPE type, int priority);

			Task * Top();
		private:
			 TaskQueue queue;

			 unsigned int id_allocator = 0;
		};
	}
}