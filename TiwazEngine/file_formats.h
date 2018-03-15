#pragma once

#include <cstdint>

#include <string>
#include <vector>

#include <GLM/glm.hpp>

namespace Tiwaz::BinaryFileFormats
{
	struct MeshData
	{
		~MeshData()
		{
			mesh_name.clear();

			m_positions.clear();
			m_normals.clear();
			m_uvs.clear();
			m_indices.clear();
		}

		std::string mesh_name = "UNDEFINED";

		std::vector<glm::vec3> m_positions;
		std::vector<glm::vec3> m_normals;
		std::vector<glm::vec2> m_uvs;
		std::vector<unsigned int> m_indices;
	};
}

namespace Tiwaz::ResourcesFileFormats
{
	struct MeshData
	{
		~MeshData()
		{
			file_path.clear();
			mesh_name.clear();

			positions.clear();
			normals.clear();
			uvs.clear();
			indices.clear();
		}

		std::string file_path = "UNDEFINED";
		std::string mesh_name = "UNDEFINED";

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uvs;
		std::vector<unsigned int> indices;
	};

	struct ModelData
	{
		~ModelData()
		{
			file_path.clear();
			model_name.clear();

			meshes.clear();
		}

		std::string file_path = "UNDEFINED";
		std::string model_name = "UNDEFINED";

		std::vector<MeshData*> meshes;
	};
}