#include "resources_loaders.h"

#include "graphic_component.h"
#include "graphic_types.h"

namespace Tiwaz::Loader
{
	void LoadMesh()
	{

	}

	void ProcessMesh(Graphic::Mesh* mesh, aiMesh* ai_mesh, const aiScene* ai_scene)
	{
		for (size_t i = 0; i < ai_mesh->mNumVertices; ++i)
		{
			glm::vec3 position;
			position.x = ai_mesh->mVertices[i].x;
			position.y = ai_mesh->mVertices[i].y;
			position.z = ai_mesh->mVertices[i].z;

			mesh->m_positions.push_back(position);

			glm::vec3 normal;
			normal.x = ai_mesh->mNormals[i].x;
			normal.y = ai_mesh->mNormals[i].y;
			normal.z = ai_mesh->mNormals[i].z;

			mesh->m_normals.push_back(normal);

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

			mesh->m_uvs.push_back(uv);
		}

		for (size_t i = 0; i < ai_mesh->mNumFaces; ++i)
		{
			aiFace ai_face = ai_mesh->mFaces[i];

			for (size_t j = 0; j < ai_face.mNumIndices; ++j)
			{
				mesh->m_indices.push_back(ai_face.mIndices[j]);
			}
		}
	}

	void ProcessMeshNode(Graphic::Model* model, aiNode* ai_node, const aiScene* ai_scene)
	{
		for (size_t i = 0; i < ai_node->mNumMeshes; ++i)
		{
			aiMesh* ai_mesh = ai_scene->mMeshes[ai_node->mMeshes[i]];

			Graphic::Mesh* temp_mesh = new Graphic::Mesh();

			ProcessMesh(temp_mesh, ai_mesh, ai_scene);
			model->m_meshes.push_back(temp_mesh);

			temp_mesh = nullptr;
			ai_mesh = nullptr;
		}

		for (size_t i = 0; i < ai_node->mNumChildren; ++i)
		{
			ProcessMeshNode(model, ai_node->mChildren[i], ai_scene);
		}
	}

	ModelData* LoadModel(const std::string & file_path)
	{
		ModelData* temp_model_data = new ModelData();

		temp_model_data->file_path = file_path;

		Assimp::Importer importer;
		const aiScene* ai_scene = importer.ReadFile(file_path, aiProcess_Triangulate | aiProcess_FlipUVs);

		aiNode* root_node = ai_scene->mRootNode;

		ProcessMeshNode(std::addressof(temp_model_data->graphic_model), root_node, ai_scene);

		root_node = nullptr;
		ai_scene = nullptr;

		return temp_model_data;
	}
}

namespace Tiwaz::Global
{
	Loader::ModelLoader* MODELLOADER;
}