#pragma once

#include <cstdint>

#include <string>
#include <array>
#include <tuple>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <thread>
#include <mutex>

#include "events.h"

namespace Tiwaz::EventSystem
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
		virtual void Call(const Event* event) = 0;
	};

	template<typename T, typename TEvent>
	class MemberFunctionHandler : public HandlerFunctionBase
	{
	public:
		typedef void(T::*MemberFunction)(TEvent*);

		MemberFunctionHandler(T* instance, MemberFunction mem_fn) : m_instance(instance), m_function(mem_fn) {};

		void Call(const Event* event)
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
			for (auto pair : m_handles)
			{
				for (auto pair2 : pair.second)
				{
					delete pair2.second;
					pair2.second = nullptr;
				}

				pair.second.clear();
			}

			m_handles.clear();
		}

		void HandleEvent(const Event* event)
		{
			if (event != nullptr)
			{
				std::type_index typeindex = typeid(*event);

				std::lock_guard<std::mutex> lock(m_handles_mutex);

				if (m_handles.find(typeindex) != m_handles.cend())
				{
					for (auto pair : m_handles[typeindex])
					{
						pair.second->Execute(event);
					}
				}
			}
		}

		template<typename T> void OneObjectEvent(const Event* event, T* obj)
		{
			if (obj != nullptr)
			{
				std::type_index typeindex = typeid(*event);
				uintptr_t pointeruint = reinterpret_cast<uintptr_t>(obj);

				std::lock_guard<std::mutex> lock(m_handles_mutex);

				if (m_handles.find(typeindex) != m_handles.cend())
				{
					if (m_handles[typeindex].find(pointeruint) != m_handles[typeindex].cend())
					{
						m_handles[typeindex][pointeruint]->Execute(event);
					}
				}
			}
		}

		template<typename TEvent, typename T> void RegisterEventFunction(void(T::*mem_fn)(TEvent*), T* obj)
		{
			if (obj != nullptr)
			{
				std::type_index typeindex = typeid(TEvent);
				uintptr_t pointeruint = reinterpret_cast<uintptr_t>(obj);

				std::lock_guard<std::mutex> lock(m_handles_mutex);

				if (m_handles.find(typeindex) == m_handles.cend() || m_handles.empty())
				{
					m_handles.insert(std::make_pair(typeindex, std::map<uintptr_t, HandlerFunctionBase*>{}));				
				}

				if (m_handles[typeindex].find(pointeruint) == m_handles[typeindex].cend() || m_handles[typeindex].empty())
				{
					m_handles[typeindex].insert(std::make_pair(pointeruint, new MemberFunctionHandler<T, TEvent>(obj, mem_fn)));
				}
			}
		}

		template<typename TEvent, typename T> void UnregisterEventFunction(T* obj)
		{
			if (obj != nullptr)
			{
				std::type_index typeindex = typeid(TEvent);
				uintptr_t pointeruint = reinterpret_cast<uintptr_t>(obj);

				std::lock_guard<std::mutex> lock(m_handles_mutex);

				if (m_handles.find(typeindex) != m_handles.cend())
				{
					delete m_handles[typeindex][pointeruint];
					m_handles[typeindex][pointeruint] = nullptr;

					m_handles[typeindex].erase(pointeruint);

					if (m_handles[typeindex].empty())
					{
						m_handles[typeindex].clear();
						m_handles.erase(typeindex);
					}
				}
			}
		}

	private:
		typedef std::map<std::type_index, std::map<uintptr_t, HandlerFunctionBase*>> MapMultiHandles;
		MapMultiHandles m_handles;

		std::mutex m_handles_mutex;
	};
}

namespace Tiwaz::Global
{
	extern EventSystem::EventHandler* ENGINEEVENTHANDLER;
}