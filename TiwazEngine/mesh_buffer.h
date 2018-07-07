#pragma once

#include <cstdint>

#include <string>
#include <vector>
#include <map>
#include <type_traits>
#include <memory>
#include <iostream>

#include <GLEW/glew.h>
#include <GLM/glm.hpp>

#include "counter.h"
#include "component.h"
#include "graphic_component.h"

#include "graphic_data_formats.h"

namespace Tiwaz::Graphic
{
	template<typename TComponent> class ComponentsManager
	{
	public:
		virtual ~ComponentsManager()
		{
			m_components_map.clear();
		}

		const uint64_t AddComponent(TComponent* component)
		{
			if (!ComponentManaged(component))
			{
				const uint64_t new_ID = m_ID_counter.NewID();

				m_components_map.insert(std::make_pair(new_ID, component));

				return new_ID;
			}

			return 0;
		}

		void RemoveComponent(TComponent* component)
		{
			if (ComponentManaged(component))
			{
				for (std::pair<uint64_t, TComponent*> component_pair : m_components_map)
				{
					if (component_pair.second == component)
					{
						m_components_map.erase(component_pair.first);

						m_ID_counter.ReleaseID(component_pair.first);
					}
				}
			}
		}

		const bool ComponentManaged(const uint64_t & ID)
		{
			if (ID != 0)
			{
				if (m_components_map.find(ID) != m_components_map.cend())
				{
					return true;
				}
			}

			return false;
		}

		const bool ComponentManaged(TComponent* component)
		{
			if (component != nullptr)
			{
				for (std::pair<uint64_t, TComponent*> component_pair : m_components_map)
				{
					if (component_pair.second == component)
					{
						return true;
					}
				}
			}

			return false;
		}

	protected:
		TComponent * AccessComponent(const uint64_t & ID)
		{
			if (ID != 0 && m_components_map.find(ID) != m_components_map.cend())
			{
				return m_components_map[ID];
			}

			return nullptr;
		}

		std::map<uint64_t, TComponent*> m_components_map;

	private:
		Counter::IDCounter m_ID_counter;
	};
}

namespace Tiwaz::Global
{
	//extern Graphic::TransformationsManager* TRANSFORMATION_MANAGER;
	//extern Graphic::MeshesManager* MESHES_MANAGER;
}