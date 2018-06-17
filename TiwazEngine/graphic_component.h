#pragma once

#include <vector>
#include <iostream>
#include <type_traits>

#include <GLM/glm.hpp>

#include "component.h"
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
			m_mesh_ID = 0;
		}

		TransformationComponent* transformation = new TransformationComponent;

	private:
		uint64_t m_mesh_ID = 0;
	};
}