#pragma once

#include <string>
#include <vector>

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
	struct Mesh
	{
		~Mesh()
		{
			m_positions.clear();
			m_normals.clear();
			m_uvs.clear();

			m_indices.clear();
		}

		std::vector<glm::vec3> m_positions;
		std::vector<glm::vec3> m_normals;
		std::vector<glm::vec2> m_uvs;

		std::vector<unsigned int> m_indices;
	};

	typedef std::vector<Mesh*> Meshes;

	struct Model
	{
		~Model()
		{
			for (auto mesh : m_meshes)
			{
				delete mesh;
				mesh = nullptr;
			}

			m_meshes.clear();
		}

		std::vector<Mesh*> m_meshes;
	};

	extern void LoadModel(const std::string & file_path, Component::ModelComponent* comp);
}