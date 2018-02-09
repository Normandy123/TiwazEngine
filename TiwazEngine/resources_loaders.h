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

	static Mesh* Load_Model(const std::string & file_path)
	{
		Mesh* output_mesh = new Mesh();

		Assimp::Importer importer;
		const aiScene* ai_scene = importer.ReadFile(file_path, aiProcess_Triangulate | aiProcess_FlipUVs);

		aiNode* root_node = ai_scene->mRootNode;

		return output_mesh;
	};
}