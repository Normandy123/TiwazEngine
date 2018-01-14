#pragma once

#include <functional>
#include <type_traits>
#include <map>
#include <string>
#include <tuple>
#include <map>
#include <sstream>
#include <ostream>
#include <any>

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

	template<typename...TArgs> class ArgsSpecFactory : public BaseSpecFactory
	{
	public:
		virtual void SetParameters(const TArgs&...args) = 0;
	};

	class BaseSpecFactory
	{
	public:
		virtual std::any Call() = 0;

		template<typename...TArgs> inline const auto GetArgsSpec() { return dynamic_cast<ArgsSpecFactory<TArgs...>*>(this); };
	};

	template<typename T, typename...TArgs> class SpecFactory : public ArgsSpecFactory<TArgs...>
	{
	public:
		void SetParameters(const TArgs&...args) override
		{
			para = std::make_tuple(args...);
		}

		std::any Call() override
		{
			return CallWithTupleArgs(ConstructObjectFunction<T, TArgs...>, para, std::index_sequence_for<TArgs...>());
		}

	protected:
		std::tuple<TArgs...> para;

	};

	class Factory
	{
	public:
		~Factory()
		{
			m_name_base_map.clear();
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

			m_name_base_map.insert(std::make_pair(type_name, new SpecFactory<T, TArgs...>));
		}

		template<typename T, typename...TArgs> auto ConstructObject(const std::string & type_name, T* holder, TArgs...args)
		{
			ArgsSpecFactory<TArgs...>* temp_fac = m_name_base_map[type_name]->GetArgsSpec<TArgs...>();
			temp_fac->SetParameters(args...);

			return std::any_cast<T*>(m_name_base_map[type_name]->Call());
		}

	private:
		std::map<std::string, BaseSpecFactory*> m_name_base_map;
	};
}

namespace Tiwaz::Global
{
	extern Factory::Factory* FACTORY;
}