#include "object_system.h"

#include "log_system.h"

namespace Tiwaz
{
	EngineObject::EngineObject()
	{

	}

	EngineObject::~EngineObject()
	{
		m_ID = 0;
	}

	void EngineObject::SetObjectID(const uint64_t & ID) { m_ID = ID; }
}

namespace Tiwaz::ObjectSystem
{
	ObjectsManager::ObjectsManager()
	{

	}

	ObjectsManager::~ObjectsManager()
	{
		for (std::pair<uint64_t, EngineObject*> object_pair : m_objects)
		{
			delete object_pair.second;
			object_pair.second = nullptr;
		}

		m_objects.clear();
		m_ID_counter.~IDCounter();
	}

	const uint64_t ObjectsManager::AddObject(EngineObject* object)
	{
		if (object->object_ID() == 0 && object != nullptr)
		{
			const uint64_t new_ID = m_ID_counter.NewID();
		
			object->SetObjectID(new_ID);
			m_objects.insert(std::make_pair(new_ID, object));
		
			return new_ID;
		}
		else
		{
			Log(LogSystem::TIWAZ_WARNING, "OBJECT_MANAGER", "Can not add object, ID is already added or pointer is nullptr");
		}

		return 0;
	}

	void ObjectsManager::RemoveObject(const uint64_t & ID)
	{
		if (m_objects.find(ID) != m_objects.cend())
		{
			m_objects[ID]->SetObjectID(0);
			m_ID_counter.ReleaseID(ID);

			m_objects[ID] = nullptr;
			m_objects.erase(ID);
		}
		else
		{
			Log(LogSystem::TIWAZ_WARNING, "OBJECT_MANAGER", "Can not remove invalid object with ID: " + std::to_string(ID));
		}
	}

	EngineObject* ObjectsManager::AccessObjectByID(const uint64_t & ID)
	{
		if (m_objects.find(ID) != m_objects.cend())
		{
			return m_objects[ID];
		}
		else
		{
			Log(LogSystem::TIWAZ_WARNING, "OBJECT_MANAGER", "Can not access invalid object with ID: " + std::to_string(ID));
		}

		return nullptr;
	}

	const bool ObjectsManager::HasObject(const uint64_t & ID)
	{
		if (m_objects.find(ID) != m_objects.cend())
		{
			return true;
		}

		return false;
	}
	const bool ObjectsManager::HasObject(EngineObject const * object)
	{
		for (std::pair<uint64_t, EngineObject*> object_pair : m_objects)
		{
			if (object_pair.second == object)
			{
				return true;
			}
		}

		return false;
	}
}

namespace Tiwaz::Global
{
	ObjectSystem::ObjectsManager* OBJECTS_MANAGER;
}