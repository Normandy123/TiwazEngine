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
			Global::ENGINEEVENTHANDLER->RegisterEventFunction(&Entity::Init, this);
			Global::ENGINEEVENTHANDLER->RegisterEventFunction(&Entity::Update, this);
			Global::ENGINEEVENTHANDLER->RegisterEventFunction(&Entity::Exit, this);
		}

		~Entity()
		{
			Global::ENGINEEVENTHANDLER->UnregisterEventFunction<EventSystem::EntityInitEvent>(this);
			Global::ENGINEEVENTHANDLER->UnregisterEventFunction<EventSystem::EntityUpdateEvent>(this);
			Global::ENGINEEVENTHANDLER->UnregisterEventFunction<EventSystem::EntityExitEvent>(this);
		}

		virtual void Init(const EventSystem::EntityInitEvent* event) {}
		virtual void Update(const EventSystem::EntityUpdateEvent* event) {}
		virtual void Exit(const EventSystem::EntityExitEvent* event) {}
	};
}