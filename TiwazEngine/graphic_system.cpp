#include "graphic_system.h"

namespace Tiwaz::Graphic
{
	GraphicManager::GraphicManager()
	{
		Global::EVENTHANDLER->RegisterEventFunction(&GraphicManager::OnScreenResize, this);
	}

	GraphicManager::~GraphicManager()
	{
		Global::EVENTHANDLER->UnregisterEventFunction<EventSystem::ScreenResizeEvent>(this);
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

	void GraphicManager::OnScreenResize(const EventSystem::ScreenResizeEvent* event)
	{
		glViewport(0, 0, event->width, event->height);
	}
}

namespace Tiwaz::Global
{
	Graphic::GraphicManager* GRAPHICMANAGER;
}