#pragma once

#include <cstdint>

#include <type_traits>

#include "object_system.h"
#include "render_scene.h"

namespace Tiwaz
{
	template<typename T, typename...TArgs> static T* CreateObject(TArgs&&...args)
	{
		if (std::is_base_of<EngineObject, T>::value)
		{
			auto obj = new T(std::forward<TArgs>(args)...);
			Global::OBJECTS_MANAGER->AddObject(obj);

			if (std::is_base_of<Component::GraphicComponent, T>::value)
			{
				Global::RENDER_SCENE->AddComponent(obj);
			}

			return obj;
		}

		return nullptr;
	}

	template<typename T> static const bool RemoveObject(T* object)
	{
		if (std::is_base_of<EngineObject, T>::value && object != nullptr)
		{
			if (std::is_base_of<Component::GraphicComponent, T>::value)
			{
				Global::RENDER_SCENE->RemoveComponent(object);
			}

			Global::OBJECTS_MANAGER->RemoveObject(object->object_ID());

			delete object;
			object = nullptr;

			return true;
		}

		return false;
	}
}