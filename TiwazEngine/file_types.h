#pragma once

#include <string>
#include <vector>

#include <GLM/glm.hpp>

namespace Tiwaz::FileFormats
{
	struct MeshData
	{
		std::string mesh_name = "test";

		size_t size_positions = 1;
		size_t size_normals = 0;
		size_t size_uvs = 0;

		std::vector<glm::vec3> positions = {glm::vec3(3, 5, 6)};
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uvs;
	};
}