#pragma once

#include <vector>
#include <iostream>
#include <type_traits>

#define GLM_FORCE_SIZE_T_LENGTH
#include <GLM/glm.hpp>

#include "component.h"
#include "log_system.h"
#include "resources_IO.h"

namespace Tiwaz::Component
{
	typedef std::vector<float> vec;

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

		const std::vector<glm::vec3> Positions() { return m_mesh->positions; }
		const std::vector<glm::vec3> Normals() { return m_mesh->normals; }
		const std::vector<glm::vec2> UVs() { return m_mesh->uvs; }

		const std::vector<unsigned int> Indices() { return m_mesh->indices; }

	private:
		BinaryFileFormats::MeshData* m_mesh;
	};
}