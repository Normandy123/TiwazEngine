#pragma once

#include <vector>
#include <iostream>
#include <type_traits>

#include <GLM/glm.hpp>

#include "component.h"
#include "log_system.h"
#include "resources_IO.h"

namespace Tiwaz::Component
{
	class GraphicComponent : public ComponentBase
	{
	public:
		GraphicComponent()
		{

		}

		~GraphicComponent()
		{
			
		}
	};

	class MeshComponent : public GraphicComponent
	{
	public:
		~MeshComponent()
		{
			m_mesh = nullptr;
		}

		void SetMesh(FileFormats::MeshData* mesh)
		{
			m_mesh = mesh;
		}

		const std::vector<glm::vec3> Positions() { return m_mesh->positions; }
		const std::vector<glm::vec3> Normals() { return m_mesh->normals; }
		const std::vector<glm::vec2> UVs() { return m_mesh->uvs; }

		const std::vector<unsigned int> Indices() { return m_mesh->indices; }

	private:
		FileFormats::MeshData* m_mesh;
	};
}