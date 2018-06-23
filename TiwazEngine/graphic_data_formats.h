#pragma once

#include <cstdint>

#include <string>
#include <vector>
#include <algorithm>

#include <GLM/glm.hpp>

namespace Tiwaz::Graphic::DataFormats
{
	struct VerticesData
	{
		~VerticesData()
		{
			positions.clear();
			normals.clear();
			uvs.clear();
			indices.clear();
		}

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uvs;
		std::vector<unsigned int> indices;
	};

	struct MeshData
	{
		~MeshData()
		{
			delete vertices;
			vertices = nullptr;
		}

		VerticesData* vertices = new VerticesData;
	};
}