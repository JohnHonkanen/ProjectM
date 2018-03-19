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

		void v1::TaskSystem::TaskManager::AddTask(Task task, int priority)
		{
			id_allocator++;

			/** Creates our Task and add it to the queue*/
			task.SetUID(id_allocator);

			queue.push(task);
		}

		Task TaskManager::Top() const
		{
			return queue.top();
		}

		Task TaskManager::Pop()
		{
			Task t = queue.top();
			queue.pop();

			return t;
		}

	}
}
