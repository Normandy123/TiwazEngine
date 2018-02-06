#pragma once

#include <string>
#include <tuple>
#include <map>
#include <typeinfo>
#include <functional>
#include <thread>

#include "object_system.h"

namespace Tiwaz::EventSystem
{
	class EventHandler 
	{
	public:
		~EventHandler()
		{
			m_object = nullptr;
			m_container_function = nullptr;
		}

		template<typename TFunction, typename...TArgs> void SetFunction(TFunction func, TArgs...args)
		{
			if (std::is_function<TFunction>::value)
			{
				m_container_function = std::bind(func, args...);
			}
		}

		template<typename TFunction, typename TObject, typename...TArgs> void SetMemberFunction(TFunction func, TObject object, TArgs...args)
		{
			if (std::is_member_function_pointer<TFunction>::value && std::is_pointer<TObject>::value && (object != nullptr))
			{
				m_container_function = std::bind(func, object, args...);
				m_object = object;
			}
		}

		void CallFunction()
		{		
			m_container_function();
		}

		void ResetFunction()
		{
			m_object = nullptr;
			m_container_function = nullptr;
		}

		const void* ObjectPointer() { return m_object; }

	private:
		std::function<void()> m_container_function;
		void* m_object = nullptr;
	};

	class EventsManager
	{
	public:
		~EventsManager()
		{
			for (auto event_pair : m_eventhandler_map)
			{
				for (auto handler_pair : event_pair.second)
				{
					handler_pair.second->ResetFunction();
					delete handler_pair.second;
					handler_pair.second = nullptr;
				}
			}

			m_eventhandler_map.clear();
		}

		template<typename TFunction, typename TObject, typename...TArgs> void AddHandle(const std::string & event_name, TObject object, TFunction func, TArgs...args)
		{
			if ((m_eventhandler_map.find(event_name) == m_eventhandler_map.cend()) || m_eventhandler_map.empty())
			{
				m_eventhandler_map.insert(std::make_pair(event_name, std::map<void*, EventHandler*>{}));
			
				//auto temp_object = Global::OBJECTMANAGER->AccessObjectByID(ID);

				EventHandler* temp_handler = new EventHandler;
				temp_handler->SetMemberFunction(func, object, args...);
			
				m_eventhandler_map[event_name].insert(std::make_pair(object, std::move(temp_handler)));

				//temp_object = nullptr;
				temp_handler = nullptr;	
			}
			else
			{
				//auto temp_object = Global::OBJECTMANAGER->AccessObjectByID(ID);

				EventHandler* temp_handler = new EventHandler;
				temp_handler->SetMemberFunction(func, object, args...);
			
				m_eventhandler_map[event_name].insert(std::make_pair(object, std::move(temp_handler)));

				//temp_object = nullptr;
				temp_handler = nullptr;
			}		
		}

		template<typename TObject> void RemoveHandle(const std::string & event_name, TObject object)
		{
			if (std::is_pointer<TObject>::value && (object != nullptr))
			{
				delete m_eventhandler_map[event_name][object];
				m_eventhandler_map[event_name][object] = nullptr;
				m_eventhandler_map[event_name].erase(object);
			}
		}

		void LaunchEvent(const std::string & event_name)
		{
			if((m_eventhandler_map.find(event_name) != m_eventhandler_map.cend()) || (!m_eventhandler_map.empty()))
			for (auto handler_pair : m_eventhandler_map[event_name])
			{
				handler_pair.second->CallFunction();
			}
		}
	private:
		std::map<std::string, std::map<void*, EventHandler*>> m_eventhandler_map;
	};
}

namespace Tiwaz::Global
{
	extern EventSystem::EventsManager* EVENTMANAGER;
}