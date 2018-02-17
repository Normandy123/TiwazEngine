#pragma once

#include <cstdint>

#include <GLEW/glew.h>
#include <GLM/glm.hpp>

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

		void ResizeScreen(const uint16_t new_width, const uint16_t new_height);
	};
}

namespace Tiwaz::Global
{
	extern Graphic::GraphicManager* GRAPHICMANAGER;
}