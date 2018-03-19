#pragma once

namespace v1
{
	namespace TaskSystem
	{
		using uint = unsigned int;
		class Task
		{
		public:
			enum TYPE {
				SEND,
				REQUEST,
				SENT_TO
			};

			static Task * Create(TYPE type, uint priority);

			//Sets/Get a ID for the task
			void SetUID(uint uniqueID);
			uint GetUID();
			//Operator Overloads for priority Queue
			bool operator< (Task const& other) { return priority < other.priority; };
			bool operator> (Task const& other) { return priority > other.priority; };
		private:
			Task(TYPE t, uint p);

			TYPE type;
			uint priority;
			uint uid;
		};
	}
}
