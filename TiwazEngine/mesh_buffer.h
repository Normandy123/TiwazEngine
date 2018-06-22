#pragma once

#include <cstdint>

#include <string>
#include <vector>
#include <map>
#include <type_traits>
#include <iostream>

#include <GLEW/glew.h>
#include <GLM/glm.hpp>

#include "counter.h"
#include "component.h"
#include "graphic_component.h"

#include "graphic_data_formats.h"

namespace Tiwaz::Graphic
{
	class MeshesManager;

	class MeshData
	{
		friend MeshesManager;
	public:
		~MeshData()
		{
			m_mesh_ID = 0;

			delete m_vertices;
			m_vertices = nullptr;
		}
		
	private:
		uint64_t m_mesh_ID = 0;

		DataFormats::VerticesData* m_vertices = new DataFormats::VerticesData;
	};

	template<typename TComponent> class ComponentsManager
	{
	public:
		~ComponentsManager()
		{
			m_components_map.clear();

			m_ID_counter.~IDCounter();
		}

		const uint64_t AddComponent(TComponent* component)
		{
			if (component != nullptr && !ComponentManaged(component))
			{
				const uint64_t new_ID = m_ID_counter.NewID();
			
				m_components_map.insert(std::make_pair(new_ID, component));

				return new_ID;
			}

			return 0;
		}

		void RemoveComponent(TComponent* component)
		{
			if (component != nullptr && ComponentManaged(component))
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

		const bool ComponentManaged(TComponent* component)
		{
			for (std::pair<uint64_t, TComponent*> component_pair : m_components_map)
			{
				if (component_pair.second == component)
				{
					return true;
				}
			}

			return false;
		}

	private:
		std::map<uint64_t, TComponent*> m_components_map;

		Counter::IDCounter m_ID_counter;
	};

	//TODO implement TransformationManager
	class TransformationsManager
	{
	public:

	};

	class MeshesManager : public ComponentsManager<Component::MeshComponent>
	{
	public:

	};

	class MeshesBuffer
	{
	protected:
		struct InstancedMesh
		{
			InstancedMesh()
			{
				glCreateVertexArrays(1, &m_vao);
				glCreateBuffers(7, m_vbos);
				glCreateBuffers(1, &m_ibo);
			}

			~InstancedMesh()
			{
				transformation_IDs.clear();

				glBindVertexArray(0);

				glDeleteBuffers(7, m_vbos);
				glDeleteBuffers(1, &m_ibo);
				glDeleteVertexArrays(1, &m_vao);
			}

			uint64_t mesh_ID = 0;
			std::vector<uint64_t> transformation_IDs;

			GLuint m_vao = 0;
			GLuint m_vbos[7] = {0};

			GLuint m_ibo = 0;
		};

	public:
		~MeshesBuffer();

		void AddMesh(const uint64_t & mesh_ID, const uint64_t & transformation_ID);
		void RemoveMesh(const uint64_t & mesh_ID, const uint64_t & transformation_ID);

		void Init();
		void Update();
		void Exit();

	private:
		std::map<uint64_t, InstancedMesh*> m_instances_map;

		Counter::IDCounter m_ID_counter;
	};
}

namespace Tiwaz::Global
{
	extern Graphic::TransformationsManager* TRANSFORMATION_MANAGER;
	extern Graphic::MeshesManager* MESHES_MANAGER;
}