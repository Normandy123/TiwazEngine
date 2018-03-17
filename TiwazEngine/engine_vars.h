#pragma once

#include <atomic>

namespace Tiwaz::Global
{
	extern double DELTA_TIME;
	extern std::atomic_bool ENGINE_IS_RUNNING;
	extern std::atomic_bool ENGINE_SHOULD_EXIT;
}