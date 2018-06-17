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

			delete vertices;
			vertices = nullptr;
		}

		std::string file_path = "UNDEFINED";
		std::string mesh_name = "UNDEFINED";

		Graphic::DataFormats::VerticesData* vertices = new Graphic::DataFormats::VerticesData;
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

		std::string file_path = "UNDEFINED";
		std::string model_name = "UNDEFINED";

		std::vector<FileFormats::MeshData*> meshes;
	};
}