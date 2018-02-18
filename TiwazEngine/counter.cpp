#include "counter.h"

Tiwaz::Counter::Counter::Counter()
{
	m_current_value = 0; m_count_value = 1; m_start_value = 0;
}

Tiwaz::Counter::Counter::Counter(const uint64_t & current_value, const uint64_t & count_value, const uint64_t & start_value)
	: m_current_value(current_value), m_count_value(count_value), m_start_value(start_value)
{

}

void Tiwaz::Counter::Counter::operator++() 
{ 
	m_current_value += m_count_value; 
}

void Tiwaz::Counter::Counter::operator+=(const uint64_t & value) 
{ 
	m_current_value += value; 
}

void Tiwaz::Counter::Counter::operator--()
{
	if ((m_current_value - m_count_value) < 0)
	{
		return;
	}
	else
	{
		m_current_value -= m_count_value;
	}
}

void Tiwaz::Counter::Counter::operator-=(const uint64_t & value)
{
	if ((m_current_value - value) < 0)
	{
		return;
	}
	else
	{
		m_current_value -= value;
	}
}

void Tiwaz::Counter::Counter::Reset()
{
	m_current_value = m_start_value;
}

Tiwaz::Counter::IDCounter::IDCounter()
{
}

Tiwaz::Counter::IDCounter::~IDCounter()
{
	m_free_IDs.clear();
}

const uint64_t Tiwaz::Counter::IDCounter::NewID()
{
	uint64_t return_value = 0;

	if (m_free_IDs.empty())
	{
		return_value = m_counter.Value();
		++m_counter;
	}
	else
	{
		return_value = m_free_IDs.front();
		m_free_IDs.pop_front();
	}

	return return_value;
}

void Tiwaz::Counter::IDCounter::ReleaseID(const uint64_t & value)
{
	if (std::find(m_free_IDs.begin(), m_free_IDs.end(), value) == m_free_IDs.cend())
	{
		m_free_IDs.emplace_back(value);
	}
}