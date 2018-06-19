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
#include "resources_IO.h"

namespace Tiwaz::Graphic
{
	class MeshesResourcesManager : public ResourcesIO::ResourcesManager<FileFormats::MeshData>
	{
	public:
		MeshesResourcesManager() : ResourcesIO::ResourcesManager<FileFormats::MeshData>(BinaryIO::ReadMesh) {}

		~MeshesResourcesManager() {}
	};

	class MeshesManager
	{
	public:
		~MeshesManager()
		{
			for (std::pair<uint64_t, FileFormats::MeshData*> mesh_pair : m_meshes_map)
			{
				mesh_pair.second = nullptr;
			}

			m_meshes_map.clear();

			m_resources_manager.~MeshesResourcesManager();
			m_ID_counter.~IDCounter();		
		}

		const uint64_t LoadFromFile(const std::string & file_path)
		{
			if (m_resources_manager.HasLoad(file_path))
			{
				FileFormats::MeshData* temp_mesh;
				const uint64_t new_ID = m_ID_counter.NewID();
			
				temp_mesh = m_resources_manager.AccessResource(file_path);
			
				m_meshes_map.insert(std::make_pair(new_ID, temp_mesh));
			
				temp_mesh = nullptr;
			
				return new_ID;
			}
			else
			{
				const uint64_t temp_res_ID = m_resources_manager.ReadAndAddResource(file_path);
			
				if (temp_res_ID != 0)
				{
					FileFormats::MeshData* temp_mesh;
					const uint64_t new_ID = m_ID_counter.NewID();
			
					temp_mesh = m_resources_manager.AccessResource(temp_res_ID);
			
					m_meshes_map.insert(std::make_pair(new_ID, temp_mesh));
			
					temp_mesh = nullptr;
			
					return new_ID;
				}
			}

			return 0;
		}

	private:
		std::map<uint64_t, FileFormats::MeshData*> m_meshes_map;

		Counter::IDCounter m_ID_counter;

		MeshesResourcesManager m_resources_manager;
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
				glBindVertexArray(0);

				glDeleteBuffers(7, m_vbos);
				glDeleteBuffers(1, &m_ibo);
				glDeleteVertexArrays(1, &m_vao);
			}

			DataFormats::VerticesData vertices;
			std::vector<glm::mat4> transformations;

			GLuint m_vao = 0;
			GLuint m_vbos[7] = {0};

			GLuint m_ibo = 0;
		};

	public:
		~MeshesBuffer();

		void Init();
		void Update();
		void Exit();

	private:

	};
}