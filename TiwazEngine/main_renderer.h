#pragma once

#include "file_formats.h"
#include "render_scene.h"
#include "g_buffer.h"
#include "event_system.h"

namespace Tiwaz::Graphic
{
	class MainRenderer
	{
	public:
		MainRenderer();
		~MainRenderer();

		void Init();
		void Update();
		void Render();
		void Exit();

		void OnScreenShow(const EventSystem::ScreenShowEvent* event);
		void OnScreenResize(const EventSystem::ScreenResizeEvent* event);

	private:
		void GeometryPass();
		void LightPass();

		GBuffer m_gbuffer;
	};
}

namespace Tiwaz::Global
{
	extern Graphic::MainRenderer* MAIN_RENDERER;
}