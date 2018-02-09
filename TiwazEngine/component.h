#pragma once

#include "commands.h"
#include "event_system.h"

namespace Tiwaz::Component
{
	class Component : public EngineObject
	{
	public:
		Component()
		{	
			Global::EVENTMANAGER->AddHandle("COMPONENT_INIT", this, &Component::Init);
			Global::EVENTMANAGER->AddHandle("COMPONENT_UPDATE", this, &Component::Update);
			Global::EVENTMANAGER->AddHandle("COMPONENT_EXIT", this, &Component::Exit);
		}

		virtual ~Component()
		{
			Global::EVENTMANAGER->RemoveHandle("COMPONENT_INIT", this);
			Global::EVENTMANAGER->RemoveHandle("COMPONENT_UPDATE", this);
			Global::EVENTMANAGER->RemoveHandle("COMPONENT_EXIT", this);
		}
	};

	template<typename T> class ComponentContainer
	{
	public:
		template<typename...TArgs> ComponentContainer(TArgs...args)
		{
			m_component = CreateObject<T>(args...);
		}

		~ComponentContainer()
		{
			RemoveObject(m_component);
			m_component = nullptr;
		}

		T* ptr ()
		{
			return m_component;
		}

	private:
		T* m_component;
	};
}