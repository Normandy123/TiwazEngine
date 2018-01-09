#pragma once

#include <cstdint>

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

		inline const uint64_t Value() { return m_current_value; }
	private:
		uint64_t m_current_value, m_count_value, m_start_value;
	};
}
