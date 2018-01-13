#pragma once

#include <functional>
#include <type_traits>
#include <map>
#include <string>
#include <tuple>
#include <map>
#include <sstream>
#include <ostream>

#include "engine_object.h"
#include "object_system.h"
#include "component.h"
#include "graphic_component.h"
#include "render_scene.h"

namespace Tiwaz::Factory
{
	template<typename T, typename...TArgs> T* ConstructObjectFunction(TArgs&&...args)
	{
		if (std::is_base_of<EngineObject, T>::value)
		{
			T* temp_object = new T(std::forward<TArgs>(args)...);

			Global::OBJECTMANAGER->AddObject(temp_object);

			if (std::is_base_of<Component::GraphicComponent, T>::value)
			{
				Global::RENDER_SCENE->AddComponent(temp_object);
			}

			return temp_object;
		}
		else
		{
			return nullptr;
		}
	}
	template<typename TFunc, typename TTuple, size_t...I> auto CallWithTupleArgs(TFunc func, TTuple tuple, std::index_sequence<I...>) 
	{
		return func(std::get<I>(std::forward<TTuple>(tuple))...);
	}

	class Factory
	{
	public:
		~Factory()
		{

		}

		template<typename T, typename...TArgs> void RegisterType()
		{
			const std::string raw_type_name = typeid(T).name();
			std::string type_name; size_t find_pos, diff_pose;

			if (std::is_base_of<EngineObject, T>::value)
			{
				find_pos = raw_type_name.find("Tiwaz::");
				diff_pose = find_pos + 7;
			}

			if (std::is_base_of<Component::Component, T>::value)
			{
				find_pos = raw_type_name.find("Tiwaz::Component::");
				diff_pose = find_pos + 18;
			}

			type_name = raw_type_name.substr(diff_pose);
		}

		template<typename...TArgs> auto ConstructObject(const std::string & type_name, TArgs...args)
		{

			
		}

	private:

	};
}

namespace Tiwaz::Global
{
	extern Factory::Factory* FACTORY;
}