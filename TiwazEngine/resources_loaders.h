#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <GLM/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>

namespace Tiwaz::Graphic
{
	struct Model;
}

namespace Tiwaz::Component
{
	class ModelComponent;
	class MeshComponent;
}

namespace Tiwaz::Loader
{
	extern Graphic::Model* LoadModel(const std::string & file_path);
}