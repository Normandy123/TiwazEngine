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

		void OnScreenShow(const EventSystem::ScreenShowEvent* event);
		void OnScreenResize(const EventSystem::ScreenResizeEvent* event);

	private:
		uint16_t m_width = 1024;
		uint16_t m_height = 576;
		float m_ratio = static_cast<float>(m_width) / static_cast<float>(m_height);
	};
}

namespace Tiwaz::Global
{
	extern Graphic::GraphicManager* GRAPHICMANAGER;
}