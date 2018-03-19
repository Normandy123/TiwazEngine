#pragma once

#include <cstdint>

#include <type_traits>

#include "object_system.h"

namespace Tiwaz
{
	template<typename T, typename...TArgs> static T* CreateObject(TArgs&&...args)
	{
		if (std::is_base_of<EngineObject, T>::value)
		{
			auto obj = new T(std::forward<TArgs>(args)...);
			Global::OBJECTS_MANAGER->AddObject(obj);

			return obj;
		}

		return nullptr;
	}

	template<typename T> static const bool RemoveObject(T* object)
	{
		if (std::is_base_of<EngineObject, T>::value && object != nullptr)
		{
			Global::OBJECTS_MANAGER->RemoveObject(object->object_ID());

			delete object;
			object = nullptr;

			return true;
		}

		return false;
	}

	template<typename T> static const bool CanDelete(T const * object)
	{
		if (std::is_base_of<EngineObject, T>::value && object != nullptr)
		{
			if (Global::OBJECTS_MANAGER->HasObject(object))
			{
				return true;
			}		
		}

		return false;
	}
}