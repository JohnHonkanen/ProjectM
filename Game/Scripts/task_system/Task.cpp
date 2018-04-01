#include "Task.h"
#include "../Structure.h"
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

		Structure * Task::From() const
		{
			return from;
		}

		Structure * Task::To() const
		{
			return to;
		}

		ResourceName Task::GetResource() const
		{
			return resource;
		}

		int Task::GetAmount() const
		{
			return amount;
		}

		Task::Task(): type(TASK_TYPE::NONE), to(nullptr)
		{
		}

		Task::Task(TYPE t) : type(t)
		{
		}

		Task::Task(TYPE t, uint p, Structure * from, Structure * to) :
			type(t), priority(p), from(from), to(to)
		{
		}

		Task::Task(TYPE t, uint p, Structure * from, Structure * to, ResourceName resource, int amount) :
			type(t), priority(p), from(from), to(to),
			resource(resource), amount(amount)
		{
		}

		Task::Task(const Task & task) : 
			type(task.type), priority(task.priority), uid(task.uid),
			from(task.from), to(task.to), resource(task.resource), amount(task.amount)
		{

		}
	}
}

