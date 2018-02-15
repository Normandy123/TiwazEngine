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
			Global::EVENTHANDLER->RegisterEventFunction(&Entity::Init, this);
			Global::EVENTHANDLER->RegisterEventFunction(&Entity::Update, this);
			Global::EVENTHANDLER->RegisterEventFunction(&Entity::Exit, this);
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