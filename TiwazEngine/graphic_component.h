#pragma once

#include <vector>
#include <iostream>
#include <type_traits>

#include <GLM/glm.hpp>

#include "component.h"
#include "render_scene.h"
#include "graphic_data_formats.h"

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

	};
}