#pragma once

#include <string>
#include <vector>

#include <GLM/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>

namespace Tiwaz::Loader
{
	struct Mesh
	{
		std::vector<glm::vec3>* m_vertices;
		std::vector<glm::vec3>* m_normals;
		std::vector<glm::vec2>* m_uvs;

		std::vector<unsigned int>* m_indices;
	};

	extern Mesh* Load_Model(const std::string & file_path);
}