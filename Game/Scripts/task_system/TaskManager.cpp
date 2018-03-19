#include "TaskManager.h"
#include "core\GameObject.h"
namespace v1
{
	namespace TaskSystem
	{
		TaskManager * TaskManager::Create(GameObject * gameObject)
		{
			TaskManager *tm = new TaskManager();
			gameObject->AddComponent(tm);

			return tm;
		}

		void TaskManager::Copy(GameObject * object)
		{
		}

		void v1::TaskSystem::TaskManager::AddTask(TASK_TYPE type, int priority)
		{
			id_allocator++;

			/** Creates our Task and add it to the queue*/
			Task t(type, priority);
			t.SetUID(id_allocator);

			queue.push(t);
		}

		Task TaskManager::Top() const
		{
			return queue.top();
		}

		void TaskManager::Pop()
		{
			queue.pop();
		}

	}
}
