#pragma once

#include "file_formats.h"
#include "render_scene.h"

namespace Tiwaz::Graphic
{
	class MainRenderer
	{
	public:
		MainRenderer()
		{

		}

		~MainRenderer()
		{

		}

		void Update()
		{
			
		}

		void Render()
		{
			if (Global::RENDER_SCENE->HasComponents())
			{

			}
		}
	};
}

namespace Tiwaz::Global
{
	extern Graphic::MainRenderer* MAIN_RENDERER;
}