#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <GLM/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>

namespace Tiwaz::Component
{
	class ModelComponent;
	class MeshComponent;
}

namespace Tiwaz::Loader
{
	extern void LoadModel(const std::string & file_path, Component::ModelComponent* model_component);
}