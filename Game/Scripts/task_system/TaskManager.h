#pragma once
#include "components\Behaviour.h"
#include <queue>
#include <vector>
#include "Task.h"
namespace v1
{
	namespace TaskSystem
	{
		struct TaskComparator
		{
			bool operator()(const Task &t1, const Task &t2) const
			{
				return t1.GetPriority() < t2.GetPriority();
			}
		};
		using TaskQueue = std::priority_queue<Task, vector<Task>, TaskComparator>;

		class TaskManager : public Behaviour
		{
		public:
			static TaskManager * Create(GameObject * gameObject);
			void Copy(GameObject * object);
			//Adds a Task to the task queue
			void AddTask(Task task, int priority);
			/** Checks to see if the task queue is not empty*/
			bool HasTask();
			/** Get the top task*/
			Task Top() const;
			/** Get the top task and remove it from the list */
			Task Pop();
		private:
			 TaskQueue queue;

			 unsigned int id_allocator = 0;
		};
	}
}