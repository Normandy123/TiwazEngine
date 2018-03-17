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
			Global::ENGINE_EVENT_HANDLER->RegisterEventFunction(&Entity::Init, this);
			Global::ENGINE_EVENT_HANDLER->RegisterEventFunction(&Entity::Update, this);
			Global::ENGINE_EVENT_HANDLER->RegisterEventFunction(&Entity::Exit, this);
		}

		~Entity()
		{
			Global::ENGINE_EVENT_HANDLER->UnregisterEventFunction<EventSystem::EntityInitEvent>(this);
			Global::ENGINE_EVENT_HANDLER->UnregisterEventFunction<EventSystem::EntityUpdateEvent>(this);
			Global::ENGINE_EVENT_HANDLER->UnregisterEventFunction<EventSystem::EntityExitEvent>(this);
		}

		virtual void Init(const EventSystem::EntityInitEvent* event) {}
		virtual void Update(const EventSystem::EntityUpdateEvent* event) {}
		virtual void Exit(const EventSystem::EntityExitEvent* event) {}
	};
}