#pragma once

#include <cstdint>

#include <string>
#include <vector>
#include <map>

#include <GLEW/glew.h>
#include <GLM/glm.hpp>

#include "counter.h"

#include "graphic_data_formats.h"
#include "binary_IO.h"

namespace Tiwaz::Graphic
{
	class MeshesManager;

	class Mesh
	{
		friend MeshesManager;
	public:
		~Mesh()
		{
			m_mesh_ID = 0;

			delete m_vertices;
			m_vertices = nullptr;
		}

		const DataFormats::VerticesData * AccessVertices() { return m_vertices; }
		
	private:
		uint64_t m_mesh_ID = 0;

		DataFormats::VerticesData* m_vertices = new DataFormats::VerticesData;
	};

	class TransformationsManager
	{
	public:
		const glm::mat4 AccessTransformation(const uint64_t & ID) {}
	private:
		std::map<uint64_t, glm::mat4> m_transformations_map;
	};

	class MeshesManager
	{
	public:
		~MeshesManager()
		{
			for (std::pair<uint64_t, Mesh*> mesh_pair : m_meshes_map)
			{
				delete mesh_pair.second;
				mesh_pair.second = nullptr;
			}

			m_meshes_map.clear();

			m_ID_counter.~IDCounter();
		}

		const uint64_t AddMesh(Mesh* mesh)
		{
			if (mesh->m_mesh_ID == 0 && mesh != nullptr)
			{
				const uint64_t new_ID = m_ID_counter.NewID();

				mesh->m_mesh_ID = new_ID;
				m_meshes_map.insert(std::make_pair(new_ID, mesh));
			}
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

		Mesh* AccessMesh(const uint64_t & ID) { return m_meshes_map[ID]; }
	private:
		std::map<uint64_t, Mesh*> m_meshes_map;

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
		~MeshesBuffer()
		{
			for (std::pair<uint64_t, InstancedMesh*> instance : m_instances_map)
			{
				delete instance.second;
				instance.second = nullptr;
			}

			m_instances_map.clear();
		}

		//TODO move class definition to source file
		void AddMesh(const uint64_t & mesh_ID, const uint64_t & transformation_ID)
		{
			if (mesh_ID != 0 && transformation_ID != 0)
			{
				for (std::pair<uint64_t, InstancedMesh*> pair : m_instances_map)
				{
					if (pair.second->mesh_ID == mesh_ID)
					{
						const std::vector<uint64_t>::iterator transformation_it = std::find(pair.second->transformation_IDs.begin(), pair.second->transformation_IDs.end(), transformation_ID);

						if (transformation_it == pair.second->transformation_IDs.cend())
						{
							pair.second->transformation_IDs.push_back(transformation_ID);

							//TODO: update transformation by IDs
						}

						break;
					}
					else
					{
						const uint64_t new_ID = m_ID_counter.NewID();

						InstancedMesh* temp_instance = new InstancedMesh;
						temp_instance->mesh_ID = mesh_ID;
						temp_instance->transformation_IDs.push_back(transformation_ID);

						//TODO: Load vertices and transformation by IDs
						Global::MESHES_MANAGER->AccessMesh(mesh_ID);

						m_instances_map.insert(std::make_pair(new_ID, temp_instance));
					}
				}
			}
		}

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