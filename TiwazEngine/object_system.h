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

		template<typename TObject, typename...TArgs>
		const uint64_t CreateAndAddObject(TArgs&&...args)
		{
			if (std::is_base_of<EngineObject, TObject>::value)
			{
				uint64_t new_ID = 0;

				if (m_free_IDs.empty())
				{
					new_ID = m_ID_counter.Value();
					++m_ID_counter;
				}
				else
				{
					new_ID = m_free_IDs.front();
					m_free_IDs.pop_front();
				}

				EngineObject* temp_object = new TObject(std::forward<TArgs>(args)...);
				temp_object->SetObjectID(new_ID);
				m_objects.insert(std::make_pair(new_ID, temp_object));

				temp_object = nullptr;

				return new_ID;
			}
			else
			{
				Message(MessageSystem::TIWAZ_WARNING, "OBJECT_MANAGER", "Can not generate and add object, which are not derived from EngineObject");
			}

			return 0;
		}

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