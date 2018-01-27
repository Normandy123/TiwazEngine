#include "python_functions.h"

namespace Tiwaz::Python
{
	const uint64_t AddObject(EngineObject* object)
	{
		return Global::OBJECTMANAGER->AddObject(object);
	}

	const std::vector<EngineObject*> Objects()
	{
		std::vector<EngineObject*> output_vec;

		for (auto pair : Global::OBJECTMANAGER->Objects())
		{
			output_vec.push_back(pair.second);
		}

		return output_vec;
	}
}