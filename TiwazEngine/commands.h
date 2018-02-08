#pragma once

#include "object_system.h"
#include "render_scene.h"

namespace Tiwaz
{
	template<typename T, typename...TArgs> T* CreateObject(TArgs...args)
	{
		if (std::is_base_of<EngineObject, T>::value)
		{
			auto obj = new T(args...);
			Global::OBJECTMANAGER->AddObject(obj);

			if (std::is_base_of<Component::GraphicComponent, T>::value)
			{
				Global::RENDER_SCENE->AddComponent(obj);
			}

			return obj;
		}

		return nullptr;
	}

	template<typename T> const bool RemoveObject(T* object)
	{
		if (std::is_base_of<EngineObject, T>::value)
		{
			if (std::is_base_of<Component::GraphicComponent, T>::value)
			{
				Global::RENDER_SCENE->RemoveComponent(object);
			}

			Global::OBJECTMANAGER->RemoveObject(object->object_ID());

			delete object;
			object = nullptr;

			return true;
		}

		return false;
	}
}