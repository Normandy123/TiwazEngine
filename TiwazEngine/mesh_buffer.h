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
	template<typename TComponent> class ComponentsManager
	{
	public:
		virtual ~ComponentsManager()
		{
			m_components_map.clear();
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

	//TODO implement TransformationManager
	class TransformationsManager : public ComponentsManager<Component::TransformationComponent>
	{
	public:

	};

	//TODO implement MeshesManager
	class MeshesManager : public ComponentsManager<Component::MeshComponent>
	{
	public:
		~MeshesManager()
		{
			for (std::pair<uint64_t, DataFormats::MeshData*> pair : m_meshdata_map)
			{
				delete pair.second;
			}

			m_meshdata_map.clear();
			m_mesh_components_map.clear();
		}

		const uint64_t AddMesh(DataFormats::MeshData* mesh)
		{
			if (mesh != nullptr)
			{
				DataFormats::MeshData* temp_mesh = new DataFormats::MeshData;
				//(*temp_mesh) = (*mesh); //TODO: real deep copying

				const uint64_t new_ID = m_ID_counter.NewID();

				m_meshdata_map.insert(std::make_pair(new_ID, temp_mesh));

				temp_mesh = nullptr;

				return new_ID;
			}

			return 0;
		}

		void SetMesh(const uint64_t & component_ID, const uint64_t & mesh_ID)
		{
			std::cout << AccessComponent(component_ID)->MeshID();
		}

	private:
		std::map<uint64_t, DataFormats::MeshData*> m_meshdata_map;
		std::map<uint64_t, std::vector<Component::MeshComponent*>> m_mesh_components_map;

		Counter::IDCounter m_ID_counter;
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