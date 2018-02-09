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
			Global::EVENTMANAGER->AddHandle("COMPONENT_INIT", this, &ComponentBase::Init);
			Global::EVENTMANAGER->AddHandle("COMPONENT_UPDATE", this, &ComponentBase::Update);
			Global::EVENTMANAGER->AddHandle("COMPONENT_EXIT", this, &ComponentBase::Exit);
		}

		virtual ~ComponentBase()
		{
			Global::EVENTMANAGER->RemoveHandle("COMPONENT_INIT", this);
			Global::EVENTMANAGER->RemoveHandle("COMPONENT_UPDATE", this);
			Global::EVENTMANAGER->RemoveHandle("COMPONENT_EXIT", this);
		}
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

		T* ptr ()
		{
			return m_component;
		}

	private:
		T* m_component;
	};
}