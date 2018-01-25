#include "python_functions.h"

namespace Tiwaz::Python
{
	const uint64_t AddObject(EngineObject* object)
	{
		return Global::OBJECTMANAGER->AddObject(object);
	}
}