#pragma once

#include <cstdint>

#include <string>
#include <vector>
#include <map>

#include <GLEW/glew.h>
#include <GLM/glm.hpp>

#include "counter.h"
#include "component.h"

#include "graphic_data_formats.h"

#include "file_formats.h"
#include "resources_IO.h"

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

	//TODO implement TransformationManager
	class TransformationsManager
	{
	public:
		const uint64_t AddTransformation(Component::TransformationComponent* component)
		{
			
		}

		const glm::mat4 Transformation(const uint64_t & ID) 
		{
			if (m_transformations_map.find(ID) != m_transformations_map.cend())
			{
				return (*m_transformations_map[ID]);
			}
		}
	private:
		std::map<uint64_t, glm::mat4*> m_transformations_map;
	};

	class MeshesManager
	{
	public:
		~MeshesManager()
		{
			for (std::pair<uint64_t, MeshData*> mesh_pair : m_meshes_map)
			{
				delete mesh_pair.second;
				mesh_pair.second = nullptr;
			}

			m_meshes_map.clear();

			m_ID_counter.~IDCounter();
		}

		const uint64_t AddMesh(MeshData* mesh)
		{
			if (mesh->m_mesh_ID == 0 && mesh != nullptr)
			{
				const uint64_t new_ID = m_ID_counter.NewID();

				mesh->m_mesh_ID = new_ID;
				m_meshes_map.insert(std::make_pair(new_ID, mesh));
			}
		}

		const uint64_t AddMesh(const std::string & file_path)
		{
			
		}

		void RemoveMesh(const uint64_t & ID)
		{
			if (m_meshes_map.find(ID) != m_meshes_map.cend())
			{
				m_ID_counter.ReleaseID(ID);

				m_meshes_map[ID] = nullptr;
				m_meshes_map.erase(ID);				
			}
		}

		void SetVertices(const uint64_t & ID, DataFormats::VerticesData vertices)
		{
			if (m_meshes_map.find(ID) != m_meshes_map.cend())
			{
				(*m_meshes_map[ID]->m_vertices) = vertices;
			}
		}

		const DataFormats::VerticesData Vertices(const uint64_t & ID) 
		{
			if (m_meshes_map.find(ID) != m_meshes_map.cend())
			{
				return (*m_meshes_map[ID]->m_vertices);
			}	
		}

		const MeshData * const AccessMesh(const uint64_t & ID)
		{
			if (m_meshes_map.find(ID) != m_meshes_map.cend())
			{
				return m_meshes_map[ID];
			}		
		}

	private:
		std::map<uint64_t, MeshData*> m_meshes_map;
		std::map<uint64_t, std::string> m_filepaths_map;

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