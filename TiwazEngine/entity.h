#pragma once

#include <iostream>

#include "object_system.h"
#include "event_system.h"

namespace Tiwaz::Entity
{
	class Entity : public EngineObject
	{
	public:
		Entity()
		{
			Global::EVENTHANDLER->RegisterEventFunction(this, &Entity::Init);
			Global::EVENTHANDLER->RegisterEventFunction(this, &Entity::Update);
			Global::EVENTHANDLER->RegisterEventFunction(this, &Entity::Exit);
		}

		~Entity()
		{
			Global::EVENTHANDLER->UnregisterEventFunction<EventSystem::EntityInitEvent>(this);
			Global::EVENTHANDLER->UnregisterEventFunction<EventSystem::EntityUpdateEvent>(this);
			Global::EVENTHANDLER->UnregisterEventFunction<EventSystem::EntityExitEvent>(this);
		}

		virtual void Init(const EventSystem::EntityInitEvent* event) {}
		virtual void Update(const EventSystem::EntityUpdateEvent* event) {}
		virtual void Exit(const EventSystem::EntityExitEvent* event) {}
	};
}