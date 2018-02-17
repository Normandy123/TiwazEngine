#include "graphic_system.h"

namespace Tiwaz::Graphic
{
	GraphicManager::GraphicManager()
	{

	}

	GraphicManager::~GraphicManager()
	{

	}
	
	void GraphicManager::Init()
	{
		glClearColor(0.2f, 0.5f, 0.7f, 1.0f);
	}

	void GraphicManager::Update()
	{

	}

	void GraphicManager::Render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glVertex3f(-0.5, 0.0, 0.0);
		glVertex3f(0.0, 0.5, 0.0);
		glVertex3f(0.5, 0.0, 0.0);
		glEnd();
	}

	void GraphicManager::Exit()
	{

	}

	void GraphicManager::ResizeScreen(const uint16_t new_width, const uint16_t new_height)
	{
		glViewport(0, 0, new_width, new_height);
	}
}

namespace Tiwaz::Global
{
	Graphic::GraphicManager* GRAPHICMANAGER;
}