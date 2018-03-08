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

		size_t size_positions = 0;
		size_t size_normals = 0;
		size_t size_uvs = 0;
		size_t size_indices = 0;

		std::vector<glm::vec3> m_positions;
		std::vector<glm::vec3> m_normals;
		std::vector<glm::vec2> m_uvs;
		std::vector<unsigned int> m_indices;

		void SetPositions(const std::vector<glm::vec3> & positions)
		{
			size_positions = positions.size();
			m_positions = positions;
		}

		void SetNormals(const std::vector<glm::vec3> & normals)
		{
			size_normals = normals.size();
			m_normals = normals;
		}

		void SetUvs(const std::vector<glm::vec2> & uvs)
		{
			size_uvs = uvs.size();
			m_uvs = uvs;
		}

		void SetIndices(const std::vector<unsigned int> & indices)
		{
			size_indices = indices.size();
			m_indices = indices;
		}
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