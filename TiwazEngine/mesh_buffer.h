#pragma once

#include <cstdint>

#include <string>
#include <vector>
#include <map>

#include <GLEW/glew.h>
#include <GLM/glm.hpp>

#include "counter.h"
#include "graphic_component.h"

#include "file_formats.h"
#include "binary_IO.h"

namespace Tiwaz::Graphic
{
	class TransformationsManager
	{
	public:
		glm::mat4 AccessTransformation(const uint64_t & ID) {}
	private:

	};

	class MeshesManager
	{
	public:
		
	private:
		std::map<uint64_t, Component::MeshComponent*> m_instances_map;
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

		void AddMeshComponent(const uint64_t & mesh_ID, const uint64_t & transformation_ID)
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