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

		const uint16_t ScreenWidth() { return m_width; }
		const uint16_t ScreenHeight() { return m_height; }
		const uint16_t HalfScreenWidth() { return m_half_width; }
		const uint16_t HalfScreenHeight() { return m_half_height; }
		
		const float ScreenRatio() { return m_ratio; }

	private:
		uint16_t m_width = 1024, m_half_width = 512;
		uint16_t m_height = 576, m_half_height = 288;

		float m_ratio = static_cast<float>(m_width) / static_cast<float>(m_height);
	};
}

namespace Tiwaz::Global
{
	extern Graphic::GraphicManager* GRAPHIC_MANAGER;
}