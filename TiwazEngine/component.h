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
			Global::EVENTHANDLER->RegisterEventFunction(&ComponentBase::Init, this);
			Global::EVENTHANDLER->RegisterEventFunction(&ComponentBase::Update, this);
			Global::EVENTHANDLER->RegisterEventFunction(&ComponentBase::Exit, this);
		}

		virtual ~ComponentBase()
		{
			Global::EVENTHANDLER->UnregisterEventFunction<EventSystem::ComponentInitEvent>(this);
			Global::EVENTHANDLER->UnregisterEventFunction<EventSystem::ComponentUpdateEvent>(this);
			Global::EVENTHANDLER->UnregisterEventFunction<EventSystem::ComponentExitEvent>(this);
		}

		virtual void Init(const EventSystem::ComponentInitEvent* event) {}
		virtual void Update(const EventSystem::ComponentUpdateEvent* event) {}
		virtual void Exit(const EventSystem::ComponentExitEvent* event) {}
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