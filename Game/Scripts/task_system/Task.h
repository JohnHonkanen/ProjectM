#pragma once

enum class TASK_TYPE {
	COLLECT,
	REQUEST,
	SEND_TO,
	MINE,
	NONE,
};

class Structure;

namespace v1
{
	namespace TaskSystem
	{
		using uint = unsigned int;
		using TYPE = TASK_TYPE;
		class Task
		{
		public:
			Task();
			Task(TYPE t);
			Task(TYPE t, uint p, Structure *from, Structure *to = nullptr);
			Task(TYPE t, uint p, Structure *from, Structure *to, ResourceName resource, int amount);
			Task(const Task& task); //copy ctor

			//Sets/Get a ID for the task
			void SetUID(uint uniqueID);
			uint GetUID() const;

			uint GetPriority() const;

			TYPE GetType() const;

			Structure *From() const;
			Structure *To() const;

			ResourceName GetResource() const;
			int GetAmount() const;

			//Operator Overloads for priority Queue
			bool operator< (Task const& other) { return priority < other.priority; };
			bool operator> (Task const& other) { return priority > other.priority; };
		private:
			TYPE type;
			uint priority;
			uint uid;
			
			Structure *from;
			Structure *to;
			ResourceName resource;
			int amount;
		};
	}
}
