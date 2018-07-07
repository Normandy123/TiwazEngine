#pragma once

#include <vector>
#include <iostream>
#include <type_traits>

#include <GLM/glm.hpp>

#include "component.h"
#include "render_scene.h"
#include "file_formats.h"
#include "binary_IO.h"

namespace Tiwaz::Graphic
{
	class MeshesManager;
}

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

	class MeshInstanceComponent : public GraphicComponent
	{
	public:
		~MeshInstanceComponent()
		{
			m_mesh_ID = 0;
		}

		//void SetMeshID(const uint64_t & ID) {}

		const uint64_t MeshID() { return m_mesh_ID; }

	private:
		uint64_t m_mesh_ID = 0;
	};
}