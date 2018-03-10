#pragma once

#include <cstdint>

#include <GLEW/glew.h>
#include <GLM/glm.hpp>

#include "event_system.h"
#include "log_system.h"

namespace Tiwaz::Graphic
{
	class GraphicManager
	{
	public:
		GraphicManager();
		~GraphicManager();

		void Init();
		void Update();
		void Render();
		void Exit();

		void OnScreenResize(const EventSystem::ScreenResizeEvent* event);
	};
}

namespace Tiwaz::Global
{
	extern Graphic::GraphicManager* GRAPHICMANAGER;
}