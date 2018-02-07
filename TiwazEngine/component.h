#pragma once

#include "object_system.h"
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
}