#include "resources_loaders.h"

namespace Tiwaz::Loader
{
	void LoadMesh()
	{

	}

	void ProcessMesh(Mesh* mesh, aiMesh* ai_mesh, const aiScene* ai_scene)
	{
		for (size_t i = 0; i < ai_mesh->mNumVertices; ++i)
		{
			glm::vec3 position;
			position.x = ai_mesh->mVertices[i].x;
			position.y = ai_mesh->mVertices[i].y;
			position.z = ai_mesh->mVertices[i].z;

			mesh->m_positions.push_back(position);
		}
	}

	void ProcessMeshNode(Model* model, aiNode* ai_node, const aiScene* ai_scene)
	{
		for (size_t i = 0; i < ai_node->mNumMeshes; ++i)
		{
			aiMesh* ai_mesh = ai_scene->mMeshes[ai_node->mMeshes[i]];

			Mesh* temp_mesh = new Mesh();

			ProcessMesh(temp_mesh, ai_mesh, ai_scene);
			model->m_meshes.push_back(temp_mesh);

			temp_mesh = nullptr;
		}

		for (size_t i = 0; i < ai_node->mNumChildren; ++i)
		{
			ProcessMeshNode(model, ai_node->mChildren[i], ai_scene);
		}
	}

	void LoadModel(const std::string & file_path, Component::ModelComponent* comp)
	{
		Model* temp_model = new Model();

		Assimp::Importer importer;
		const aiScene* ai_scene = importer.ReadFile(file_path, aiProcess_Triangulate | aiProcess_FlipUVs);

		aiNode* root_node = ai_scene->mRootNode;

		ProcessMeshNode(temp_model, root_node, ai_scene);

		delete temp_model;
		temp_model = nullptr;
	}
}