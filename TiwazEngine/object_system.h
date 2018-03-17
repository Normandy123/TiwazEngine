#pragma once

#include <cstdint>

#include <string>
#include <deque>
#include <map>
#include <type_traits>
#include <memory>

#include "counter.h"
#include "events.h"

namespace Tiwaz::ObjectSystem
{
	class ObjectsManager;
}

namespace Tiwaz
{
	class EngineObject
	{
	friend ObjectSystem::ObjectsManager;

	public:
		EngineObject();
		virtual ~EngineObject();

		virtual void OnInit(const EventSystem::InitEvent* event) {};
		virtual void OnUpdate(const EventSystem::UpdateEvent* event) {};
		virtual void OnExit(const EventSystem::ExitEvent* event) {};

		const uint64_t object_ID() { return m_ID; }

	protected:
		uint64_t m_ID = 0;

	private:
		void SetObjectID(const uint64_t & ID);
	};
}

namespace Tiwaz::ObjectSystem
{
	class ObjectsManager
	{
	public:
		ObjectsManager();

		ObjectsManager(const ObjectsManager & other)	= delete;
		ObjectsManager(ObjectsManager && other)		= delete;

		ObjectsManager& operator=(const ObjectsManager & other)	= delete;
		ObjectsManager& operator=(ObjectsManager && other)		= delete;

		~ObjectsManager();

		const uint64_t AddObject(EngineObject* object);

		void RemoveObject(const uint64_t & ID);

		EngineObject* AccessObjectByID(const uint64_t & ID);

		const std::map<uint64_t, EngineObject*> Objects_Map() { return m_objects; }

	private:
		std::map<uint64_t, EngineObject*> m_objects;

		Counter::IDCounter m_ID_counter;
	};
}

namespace Tiwaz::Global
{
	extern ObjectSystem::ObjectsManager* OBJECTS_MANAGER;
}