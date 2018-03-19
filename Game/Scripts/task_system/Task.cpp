#include "Task.h"

namespace v1
{
	namespace TaskSystem
	{
		void Task::SetUID(uint in_uid)
		{
			uid = in_uid;
		}

		uint Task::GetUID() const
		{
			return uid;
		}

		uint Task::GetPriority() const
		{
			return priority;
		}

		TYPE Task::GetType() const
		{
			return type;
		}

		Task::Task(): type(TASK_TYPE::NONE)
		{
		}

		Task::Task(TYPE t) : type(t)
		{
		}

		Task::Task(TYPE t, uint p) :
			type(t), priority(p)
		{

		}

		Task::Task(const Task & task) : 
			type(task.type), priority(task.priority), uid(task.uid)
		{

		}
	}
}

