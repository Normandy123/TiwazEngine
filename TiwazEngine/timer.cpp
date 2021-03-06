#include "timer.h"

Tiwaz::Timer::Timer::Timer()
{

}

Tiwaz::Timer::Timer::~Timer()
{

}

void Tiwaz::Timer::Timer::Start()
{
	t1 = std::chrono::high_resolution_clock::now();
}

void Tiwaz::Timer::Timer::Reset()
{
	t1 = std::chrono::high_resolution_clock::now();
	m_last_delta_time = 0.0;
}

const double Tiwaz::Timer::Timer::DeltaTime()
{
	std::chrono::high_resolution_clock::duration temp_dt = std::chrono::high_resolution_clock::now() - t1;

	std::chrono::duration<double> duration_time = std::chrono::duration_cast<std::chrono::duration<double>>(temp_dt);

	m_last_delta_time = duration_time.count();

	return m_last_delta_time;
}