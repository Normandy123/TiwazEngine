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