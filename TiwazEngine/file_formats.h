#pragma once

#include <cstdint>

#include <string>
#include <vector>

#include <GLM/glm.hpp>

#include "graphic_data_formats.h"

namespace Tiwaz::FileFormats
{
	struct MeshData
	{
		~MeshData()
		{
			mesh_name.clear();
		}

		std::string mesh_name = "UNDEFINED";

		Graphic::DataFormats::MeshData graphic_data;
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
			}

			meshes.clear();
		}

		std::string file_path = "UNDEFINED";
		std::string model_name = "UNDEFINED";

		std::vector<FileFormats::MeshData*> meshes;
	};
}