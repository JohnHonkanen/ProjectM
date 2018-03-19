#include "Task.h"

namespace v1
{
	namespace TaskSystem
	{
		Task * Task::Create(TYPE type, uint priority)
		{
			Task * t = new Task(type, priority);
			return t;
		}

		void Task::SetUID(uint in_uid)
		{
			uid = in_uid;
		}

		uint Task::GetUID()
		{
			return uid;
		}

		Task::Task(TYPE t, uint p) : 
			type(t), priority(p)
		{

		}
	}
}

