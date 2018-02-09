#include "resources_loaders.h"

namespace Tiwaz::Loader
{
	Mesh* Load_Model(const std::string & file_path)
	{
		Mesh* output_mesh = new Mesh();

		Assimp::Importer importer;
		const aiScene* ai_scene = importer.ReadFile(file_path, aiProcess_Triangulate | aiProcess_FlipUVs);

		aiNode* root_node = ai_scene->mRootNode;

		return output_mesh;
	};
}