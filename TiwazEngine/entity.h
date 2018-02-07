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
			Global::EVENTMANAGER->AddHandle("ENTITY_INIT", this, &Entity::Init);
			Global::EVENTMANAGER->AddHandle("ENTITY_UPDATE", this, &Entity::Update);
			Global::EVENTMANAGER->AddHandle("ENTITY_EXIT", this, &Entity::Exit);
		}

		~Entity()
		{
			Global::EVENTMANAGER->RemoveHandle("ENTITY_INIT", this);
			Global::EVENTMANAGER->RemoveHandle("ENTITY_UPDATE", this);
			Global::EVENTMANAGER->RemoveHandle("ENTITY_EXIT", this);
		}
	};
}