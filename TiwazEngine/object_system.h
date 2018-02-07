#pragma once

#include <cstdint>

#include <string>
#include <deque>
#include <map>
#include <type_traits>
#include <memory>

#include "message_system.h"
#include "counter.h"
#include "render_scene.h"

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

namespace Tiwaz
{
	template<typename T, typename...TArgs> T CreateObjectS(TArgs...args)
	{
		if (std::is_base_of<EngineObject, T>::value)
		{
			auto obj = new T(args...);
			Global::OBJECTMANAGER->AddObject(obj);

			if (std::is_base_of<Component::GraphicComponent, T>::value)
			{
				Global::RENDER_SCENE->AddComponent(obj);
			}

			return *obj;
		}
	}

	template<typename T, typename...TArgs> T* CreateObject(TArgs...args)
	{
		if (std::is_base_of<EngineObject, T>::value)
		{
			auto obj = new T(args...);
			Global::OBJECTMANAGER->AddObject(obj);

			if (std::is_base_of<Component::GraphicComponent, T>::value)
			{
				Global::RENDER_SCENE->AddComponent(obj);
			}

			return obj;
		}

		return nullptr;
	}

	template<typename T> const bool RemoveObjectS(T* object)
	{
		if (std::is_base_of<EngineObject, T>::value)
		{
			if (std::is_base_of<Component::GraphicComponent, T>::value)
			{
				Global::RENDER_SCENE->RemoveComponent(object);
			}

			Global::OBJECTMANAGER->RemoveObject(object->object_ID());

			return true;
		}

		return false;
	}

	template<typename T> const bool RemoveObject(T* object)
	{
		if (std::is_base_of<EngineObject, T>::value)
		{
			if (std::is_base_of<Component::GraphicComponent, T>::value)
			{
				Global::RENDER_SCENE->RemoveComponent(object);
			}

			Global::OBJECTMANAGER->RemoveObject(object->object_ID());

			delete object;
			object = nullptr;

			return true;
		}

		return false;
	}
}