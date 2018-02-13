#pragma once

#include <string>
#include <tuple>
#include <map>
#include <typeinfo>
#include <functional>
#include <thread>

#include "object_system.h"
#include "events.h"

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
				auto lam = [=]() { std::invoke(func, args...); };

				m_container_function = lam;
			}
		}

		template<typename TFunction, typename TObject, typename...TArgs> void SetMemberFunction(TFunction func, TObject object, TArgs...args)
		{
			if (std::is_member_function_pointer<TFunction>::value && std::is_pointer<TObject>::value && (object != nullptr))
			{
				auto lam = [=]() { std::invoke(func, object, args...); };

				m_container_function = lam;
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

				if (m_eventhandler_map[event_name].empty())
				{
					m_eventhandler_map.erase(event_name);
				}
			}
		}

		void LaunchEvent(const std::string & event_name)
		{
			if (m_eventhandler_map.find(event_name) != m_eventhandler_map.cend())
			{
				for (auto handler_pair : m_eventhandler_map[event_name])
				{
					handler_pair.second->CallFunction();
				}
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

namespace Tiwaz::EventSystem2
{
	class HandlerFunctionBase
	{
	public:
		virtual ~HandlerFunctionBase() {};

		void Execute(const EventSystem::Event* event) 
		{ 
			Call(event); 
		}

	private:
		virtual void Call(const EventSystem::Event* event) = 0;
	};

	template<typename T, typename TEvent>
	class MemberFunctionHandler : public HandlerFunctionBase
	{
	public:
		typedef void(T::*MemberFunction)(TEvent*);

		MemberFunctionHandler(T* instance, MemberFunction mem_fn) : m_instance(instance), m_function(mem_fn) {};

		void Call(const EventSystem::Event* event)
		{
			(m_instance->*m_function)(static_cast<TEvent*>(event));
		}

	private:
		T* m_instance;
		MemberFunction m_function;
	};

	class EventHandler
	{
	public:
		~EventHandler()
		{
			for (auto pair : m_handlers)
			{
				delete pair.second;
				pair.second = nullptr;
			}

			m_handlers.clear();
		}

		void HandleEvent(const EventSystem::Event* event)
		{
			MapHandlers::iterator it = m_handlers.find(typeid(*event).raw_name());

			if (it != m_handlers.cend())
			{
				it->second->Execute(event);
			}
		}

		template<typename T, typename TEvent> void RegisterEventFunction(T* obj, void(T::*mem_fn)(TEvent*))
		{
			const char* type_name = typeid(TEvent).raw_name();

			MapHandlers::iterator it = m_handlers.find(type_name);

			if (obj != nullptr)
			{
				if (it == m_handlers.cend() || m_handlers.empty())
				{
					m_handlers.insert(std::make_pair(type_name, new MemberFunctionHandler<T, TEvent>(obj, mem_fn)));
				}
			}

			type_name = nullptr;
		}

		template<typename TEvent> void UnregisterEventFunction()
		{
			const char* type_name = typeid(TEvent).raw_name();

			MapHandlers::iterator it = m_handlers.find(type_name);

			if (it != m_handlers.cend())
			{
				delete it->second;
				it->second = nullptr;

				m_handlers.erase(it);
			}

			type_name = nullptr;
		}

	private:
		typedef std::map<const char*, HandlerFunctionBase*> MapHandlers;
		MapHandlers m_handlers;
	};
}