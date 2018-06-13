#include "engine_vars.h"

namespace Tiwaz::Global
{
	double DELTA_TIME = 0.0;
	std::atomic_bool ENGINE_IS_RUNNING = false;
	std::atomic_bool ENGINE_SHOULD_EXIT = true;
	std::atomic_bool ENGINE_DEBUG = false;
	std::atomic_bool ENGINE_EDITOR = false;
}