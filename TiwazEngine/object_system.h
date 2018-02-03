#pragma once

#include <cstdint>

#include <string>
#include <deque>
#include <map>
#include <type_traits>
#include <memory>

#include "engine_object.h"
#include "message_system.h"
#include "counter.h"

namespace Tiwaz::ObjectSystem
{
	class ObjectManager
	{
	public:
		ObjectManager()
		{
			
		}

		~ObjectManager()
		{
			for (auto object_pair : m_objects)
			{
				//delete object_pair.second;
				object_pair.second = nullptr;
			}

			m_objects.clear();
			m_free_IDs.clear();
		}

		template<typename TObject, typename...TArgs> const uint64_t CreateAndAddObject(TArgs&&...args)
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

		const uint64_t AddObject(EngineObject* object)
		{
			if (object != nullptr && (m_objects.find(object->object_ID()) == m_objects.cend()))
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

				object->SetObjectID(new_ID);
				m_objects.insert(std::make_pair(new_ID, object));

				return new_ID;
			}
			else
			{
				Message(MessageSystem::TIWAZ_WARNING, "OBJECT_MANAGER", "Can not add object, pointer is nullptr");
			}

			return 0;
		}

		void RemoveObject(const uint64_t & ID)
		{
			if (m_objects.find(ID) != m_objects.cend() || (!m_objects.empty()))
			{
				m_free_IDs.emplace_back(ID);
				//delete m_objects[ID];
				m_objects[ID] = nullptr;
				m_objects.erase(ID);
			}
			else
			{
				Message(MessageSystem::TIWAZ_WARNING, "OBJECT_MANAGER", "Can not remove invalid object with ID: " + std::to_string(ID));
			}
		}

		EngineObject* AccessObjectByID(const uint64_t & ID)
		{
			if ((m_objects.find(ID) != m_objects.cend()) || (!m_objects.empty()))
			{
				return m_objects[ID];
			}
			else
			{
				Message(MessageSystem::TIWAZ_WARNING, "OBJECT_MANAGER", "Can not access invalid object with ID: " + std::to_string(ID));
			}

			return nullptr;
		}

		const std::map<uint64_t, EngineObject*> Objects()
		{
			return m_objects;
		}

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