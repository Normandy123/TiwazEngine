#pragma once

#include "object_system.h"
#include "event_system.h"

namespace Tiwaz::Entity
{
	class Entity : public EngineObject
	{
	public:
		Entity()
		{
			Global::ENGINE_EVENT_HANDLER->RegisterEventFunction(&Entity::OnInit, this);
			Global::ENGINE_EVENT_HANDLER->RegisterEventFunction(&Entity::OnUpdate, this);
			Global::ENGINE_EVENT_HANDLER->RegisterEventFunction(&Entity::OnExit, this);
		}

		~Entity()
		{
			Global::ENGINE_EVENT_HANDLER->UnregisterEventFunction<EventSystem::EntityInitEvent>(this);
			Global::ENGINE_EVENT_HANDLER->UnregisterEventFunction<EventSystem::EntityUpdateEvent>(this);
			Global::ENGINE_EVENT_HANDLER->UnregisterEventFunction<EventSystem::EntityExitEvent>(this);
		}

		virtual void OnInit(const EventSystem::EntityInitEvent* event) {}
		virtual void OnUpdate(const EventSystem::EntityUpdateEvent* event) {}
		virtual void OnExit(const EventSystem::EntityExitEvent* event) {}
	};
}