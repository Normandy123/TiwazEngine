#pragma once

#include <vector>
#include <iostream>

#include <GLM/glm.hpp>

#include "component.h"

namespace Tiwaz::Component
{
	class GraphicComponent : public Component
	{

	};

	class MeshComponent : public GraphicComponent
	{
	public:
		MeshComponent()
		{

		}

		~MeshComponent()
		{
			m_vertices.clear();
			m_normals.clear();
			m_uvs.clear();
		}

		inline const std::vector<glm::vec3> Vertices() { return m_vertices; }
		inline const std::vector<glm::vec3> Normals() { return m_normals; }
		inline const std::vector<glm::vec2> UVs() { return m_uvs; }
	private:
		std::vector<glm::vec3> m_vertices;
		std::vector<glm::vec3> m_normals;
		std::vector<glm::vec2> m_uvs;
	};

	class ModelComponent : public GraphicComponent
	{

	};
}