#include "object_system.h"

namespace Tiwaz
{
	EngineObject::EngineObject()
	{
		Global::OBJECTMANAGER->AddObject(this);
	}

	EngineObject::~EngineObject()
	{

	}

	void EngineObject::SetObjectID(const uint64_t & ID) { m_ID = ID; }
}

namespace Tiwaz::ObjectSystem
{
	ObjectManager::ObjectManager()
	{

	}

	ObjectManager::~ObjectManager()
	{
		for (std::pair<uint64_t, EngineObject*> object_pair : m_objects)
		{
			object_pair.second->SetObjectID(0);
			delete object_pair.second;
			object_pair.second = nullptr;
		}

		m_objects.clear();
		m_free_IDs.clear();
	}

	const uint64_t ObjectManager::AddObject(EngineObject* object)
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

	void ObjectManager::RemoveObject(const uint64_t & ID)
	{
		if (m_objects.find(ID) != m_objects.cend() || (!m_objects.empty()))
		{
			m_objects[ID]->SetObjectID(0);
			m_free_IDs.emplace_back(ID);
			delete m_objects[ID];
			m_objects[ID] = nullptr;
			m_objects.erase(ID);
		}
		else
		{
			Message(MessageSystem::TIWAZ_WARNING, "OBJECT_MANAGER", "Can not remove invalid object with ID: " + std::to_string(ID));
		}
	}

	EngineObject* ObjectManager::AccessObjectByID(const uint64_t & ID)
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
}

namespace Tiwaz::Global
{
	ObjectSystem::ObjectManager* OBJECTMANAGER;
}