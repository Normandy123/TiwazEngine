#pragma once

#include <vector>
#include <iostream>
#include <type_traits>

#include <GLM/glm.hpp>

#include "component.h"
#include "file_formats.h"
#include "render_scene.h"

namespace Tiwaz::Component
{
	class GraphicComponent : public ComponentBase
	{
	public:
		GraphicComponent()
		{
			Global::RENDER_SCENE->AddComponent(this);
		}

		virtual ~GraphicComponent()
		{
			Global::RENDER_SCENE->RemoveComponent(this);
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