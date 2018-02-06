#pragma once

#include <cstdint>

#include <string>
#include <deque>
#include <map>
#include <type_traits>
#include <memory>

#include "message_system.h"
#include "counter.h"

namespace Tiwaz::ObjectSystem
{
	class ObjectManager;
}

namespace Tiwaz
{
	class EngineObject
	{
	friend ObjectSystem::ObjectManager;

	public:
		EngineObject();
		virtual ~EngineObject();

		virtual void Init() {}
		virtual void Update() {}
		virtual void Exit() {}	

		constexpr const uint64_t object_ID() { return m_ID; }

	protected:
		uint64_t m_ID = 0;

	private:
		void SetObjectID(const uint64_t & ID);
	};
}

namespace Tiwaz::ObjectSystem
{
	class ObjectManager
	{
	public:
		ObjectManager();
		~ObjectManager();

		template<typename TObject, typename...TArgs> const uint64_t CreateAndAddObject(TArgs&&...args);
		const uint64_t AddObject(EngineObject* object);

		void RemoveObject(const uint64_t & ID);

		EngineObject* AccessObjectByID(const uint64_t & ID);

		const std::map<uint64_t, EngineObject*> Objects() { return m_objects; }

	private:
		std::map<uint64_t, EngineObject*> m_objects;

		Counter::Counter m_ID_counter = Counter::Counter(1, 1, 1);
		std::deque<uint64_t> m_free_IDs;
	};
}

namespace Tiwaz::Global
{
	extern ObjectSystem::ObjectManager* OBJECTMANAGER;
}