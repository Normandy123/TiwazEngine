#pragma once

#include <string>
#include <vector>

#include <GLM/glm.hpp>

namespace Tiwaz::Graphic
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

	struct Model
	{
		~Model()
		{
			for (Mesh* mesh : m_meshes)
			{
				mesh = nullptr;
			}

			m_meshes.clear();
		}

		std::vector<Mesh*> m_meshes;
	};
}