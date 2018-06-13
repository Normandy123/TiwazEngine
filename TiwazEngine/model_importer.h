#pragma once

#include <string>
#include <vector>

#include <GLM/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>

#include "file_formats.h"
#include "binary_IO.h"

namespace Tiwaz::ModelImporter
{
	extern void LoadModel(const std::string & file_path, FileFormats::ModelData* model);
}