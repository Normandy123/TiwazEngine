#pragma once

#include <cstdint>

#include "object_system.h"

namespace Tiwaz::Python
{
	extern const uint64_t AddObject(EngineObject* object);
	extern const std::vector<EngineObject*> Objects();
}