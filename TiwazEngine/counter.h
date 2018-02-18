#pragma once

#include <cstdint>
#include <deque>

namespace Tiwaz::Counter
{
	class Counter
	{
	public:
		Counter();
		Counter(const uint64_t & current_value, const uint64_t & count_value, const uint64_t & start_value);

		void operator++();
		void operator+=(const uint64_t & value);

		void operator--();
		void operator-=(const uint64_t & value);

		void Reset();

		const uint64_t Value() { return m_current_value; }
	private:
		uint64_t m_current_value, m_count_value, m_start_value;
	};

	class IDCounter
	{
	public:
		IDCounter();
		~IDCounter();

		const uint64_t NewID();
		void ReleaseID(const uint64_t & value);
	private:
		Counter m_counter = Counter(1, 1, 1);
		std::deque<uint64_t> m_free_IDs;
	};
}
