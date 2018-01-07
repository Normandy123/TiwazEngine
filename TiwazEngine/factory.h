#pragma once

#include <functional>
#include <type_traits>
#include <map>
#include <string>
#include <tuple>
#include <map>

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

	class BaseArgsHolder
	{
	public:
		template<typename...TArgs> inline constexpr auto GetArgsHolder() { return static_cast<ArgsHolder<TArgs...>*>(this); }
	};

	template<typename...TArgs> class ArgsHolder : public BaseArgsHolder
	{
	public:
		template<typename...TArgs> void SetParameters(const TArgs&...args)
		{
			m_parameters = std::make_tuple(args...);
		}

		inline const std::tuple<TArgs...> Parameters() { return m_parameters; }

	protected:
		std::tuple<TArgs...> m_parameters;
	};

	class BaseSpecFactory
	{
	public:
		virtual EngineObject* Call() = 0;
	};

	template<typename T, typename...TArgs> class SpecFactory : public BaseSpecFactory
	{
	public:
		T* Call()
		{
			return CallWithTupleArgs(ConstructObjectFunction<T, TArgs...>, m_Args->Parameters(), std::index_sequence_for<TArgs...>());
		}

		void SetArgHolder(ArgsHolder<TArgs...>* arg_holder)
		{
			m_Args = arg_holder;
		}

	protected:
		ArgsHolder<TArgs...>* m_Args;
	};

	class Factory
	{
	public:
		~Factory()
		{
			for (auto pair : m_name_basespecfactory_map)
			{
				delete pair.second;
				pair.second = nullptr;
			}

			for (auto pair : m_name_baseholder_map)
			{
				delete pair.second;
				pair.second = nullptr;
			}

			m_name_basespecfactory_map.clear();
			m_name_baseholder_map.clear();
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

			SpecFactory<T, TArgs...>* m1 = new SpecFactory<T, TArgs...>();
			ArgsHolder<TArgs...>* m2 = new ArgsHolder<TArgs...>();
			m1->SetArgHolder(m2);
		
			m_name_basespecfactory_map.insert(std::make_pair(type_name, m1));
			m_name_baseholder_map.insert(std::make_pair(type_name, m2));
		}

		template<typename...TArgs> auto ConstructObject(const std::string & type_name, TArgs...args)
		{
			ArgsHolder<TArgs...>* temp_holder = m_name_baseholder_map[type_name]->GetArgsHolder<TArgs...>();
			temp_holder->SetParameters(args...);
			auto mm = m_name_basespecfactory_map[type_name]->Call();
			std::cout << typeid(mm).name() << std::endl;
		}

	private:
		std::map<std::string, BaseSpecFactory*> m_name_basespecfactory_map;
		std::map<std::string, BaseArgsHolder*>m_name_baseholder_map;
	};
}

namespace Tiwaz::Global
{
	extern Factory::Factory* FACTORY;
}