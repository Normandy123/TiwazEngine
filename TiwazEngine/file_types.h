#pragma once

#include <string>
#include <vector>

#include <GLM/glm.hpp>

namespace Tiwaz::FileFormats
{
	struct MeshData
	{
		std::string mesh_name;

		size_t size_positions = 0;
		size_t size_normals = 0;
		size_t size_uvs = 0;
		size_t size_indices = 0;

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uvs;
		std::vector<unsigned int> indices;
	};
}