#include "model_importer.h"

namespace Tiwaz::ModelImporter
{
	void ProcessMesh(FileFormats::MeshData* mesh, aiMesh* ai_mesh, const aiScene* ai_scene)
	{
		mesh->mesh_name = ai_mesh->mName.C_Str();

		for (size_t i = 0; i < ai_mesh->mNumVertices; ++i)
		{
			glm::vec3 position;
			position.x = ai_mesh->mVertices[i].x;
			position.y = ai_mesh->mVertices[i].y;
			position.z = ai_mesh->mVertices[i].z;

			mesh->positions.push_back(position);

			glm::vec3 normal;
			normal.x = ai_mesh->mNormals[i].x;
			normal.y = ai_mesh->mNormals[i].y;
			normal.z = ai_mesh->mNormals[i].z;

			mesh->normals.push_back(normal);

			glm::vec2 uv;

			if (ai_mesh->HasTextureCoords(0))
			{
				uv.x = ai_mesh->mTextureCoords[0][i].x;
				uv.y = ai_mesh->mTextureCoords[0][i].y;
			}
			else
			{
				uv = glm::vec2(0.0f, 0.0f);
			}

			mesh->uvs.push_back(uv);
		}

		for (size_t i = 0; i < ai_mesh->mNumFaces; ++i)
		{
			aiFace ai_face = ai_mesh->mFaces[i];

			for (size_t j = 0; j < ai_face.mNumIndices; ++j)
			{
				mesh->indices.push_back(ai_face.mIndices[j]);
			}
		}
	}

	void ProcessMeshNode(FileFormats::ModelData* model, aiNode* ai_node, const aiScene* ai_scene)
	{
		for (size_t i = 0; i < ai_node->mNumMeshes; ++i)
		{
			aiMesh* ai_mesh = ai_scene->mMeshes[ai_node->mMeshes[i]];

			FileFormats::MeshData* temp_mesh = new FileFormats::MeshData();

			ProcessMesh(temp_mesh, ai_mesh, ai_scene);

			model->meshes.push_back(temp_mesh);

			temp_mesh = nullptr;
			ai_mesh = nullptr;
		}

		for (size_t i = 0; i < ai_node->mNumChildren; ++i)
		{
			ProcessMeshNode(model, ai_node->mChildren[i], ai_scene);
		}
	}

	void LoadModel(const std::string & file_path, FileFormats::ModelData* model)
	{
		model->file_path = file_path;

		Assimp::Importer importer;
		const aiScene* ai_scene = importer.ReadFile(file_path, aiProcess_Triangulate);

		aiNode* root_node = ai_scene->mRootNode;

		ProcessMeshNode(model, root_node, ai_scene);

		root_node = nullptr;
		ai_scene = nullptr;
	}
}