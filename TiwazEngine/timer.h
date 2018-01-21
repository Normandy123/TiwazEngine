#pragma once

#include <chrono>

namespace Tiwaz::Timer
{
	class Timer
	{
	public:
		Timer();
		~Timer();

		void Start();
		void Reset();

		const double DeltaTime();
		inline constexpr const double LastDeltaTime() { return m_last_delta_time; }

	private:
		std::chrono::high_resolution_clock::time_point t1;
		double m_last_delta_time = 0.0;
	};
}