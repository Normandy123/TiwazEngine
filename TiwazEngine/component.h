#pragma once

#include "commands.h"
#include "event_system.h"

namespace Tiwaz::Component
{
	class ComponentBase : public EngineObject
	{
	public:
		ComponentBase()
		{	
			Global::EVENTHANDLER->RegisterEventFunction(&ComponentBase::OnInit, this);
			Global::EVENTHANDLER->RegisterEventFunction(&ComponentBase::OnUpdate, this);
			Global::EVENTHANDLER->RegisterEventFunction(&ComponentBase::OnExit, this);
		}

		virtual ~ComponentBase()
		{
			Global::EVENTHANDLER->UnregisterEventFunction<EventSystem::ComponentInitEvent>(this);
			Global::EVENTHANDLER->UnregisterEventFunction<EventSystem::ComponentUpdateEvent>(this);
			Global::EVENTHANDLER->UnregisterEventFunction<EventSystem::ComponentExitEvent>(this);
		}

		virtual void OnInit(const EventSystem::ComponentInitEvent* event) {}
		virtual void OnUpdate(const EventSystem::ComponentUpdateEvent* event) {}
		virtual void OnExit(const EventSystem::ComponentExitEvent* event) {}
	};

	template<typename T> class Component
	{
	public:
		template<typename...TArgs> Component(TArgs...args)
		{
			m_component = CreateObject<T>(args...);
		}

		~Component()
		{
			RemoveObject(m_component);
			m_component = nullptr;
		}

		T* ptr()
		{
			return m_component;
		}

	private:
		T* m_component;
	};
}