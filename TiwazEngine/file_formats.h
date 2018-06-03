#pragma once

#include <cstdint>

#include <string>
#include <vector>

#include <GLM/glm.hpp>

namespace Tiwaz::FileFormats
{
	struct MeshData
	{
		~MeshData()
		{
			mesh_name.clear();

			positions.clear();
			normals.clear();
			uvs.clear();
			indices.clear();
		}

		uint64_t ID = 0;

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

			for (FileFormats::MeshData* mesh : meshes)
			{
				delete mesh;
				mesh = nullptr;
			}

			meshes.clear();
		}

		uint64_t ID = 0;

		std::string file_path = "UNDEFINED";
		std::string model_name = "UNDEFINED";

		std::vector<FileFormats::MeshData*> meshes;
	};
}