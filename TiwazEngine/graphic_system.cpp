#include "graphic_system.h"

namespace Tiwaz::Graphic
{
	GraphicManager::GraphicManager()
	{
		Global::ENGINEEVENTHANDLER->RegisterEventFunction(&GraphicManager::OnScreenShow, this);
		Global::ENGINEEVENTHANDLER->RegisterEventFunction(&GraphicManager::OnScreenResize, this);
	}

	GraphicManager::~GraphicManager()
	{
		Global::ENGINEEVENTHANDLER->UnregisterEventFunction<EventSystem::ScreenShowEvent>(this);
		Global::ENGINEEVENTHANDLER->UnregisterEventFunction<EventSystem::ScreenResizeEvent>(this);
	}
	
	void GraphicManager::Init()
	{
		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK)
		{
			Log(LogSystem::TIWAZ_FATALERROR, "WINDOW", "Could not intialize GLEW!");
		}

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

	void GraphicManager::OnScreenShow(const EventSystem::ScreenShowEvent* event)
	{
		glViewport(0, 0, event->width, event->height);

		m_width = event->width; m_height = event->height;
		m_ratio = static_cast<float>(m_width) / static_cast<float>(m_height);
	}

	void GraphicManager::OnScreenResize(const EventSystem::ScreenResizeEvent* event)
	{
		glViewport(0, 0, event->width, event->height);

		m_width = event->width; m_height = event->height;
		m_ratio = static_cast<float>(m_width) / static_cast<float>(m_height);
	}
}

namespace Tiwaz::Global
{
	Graphic::GraphicManager* GRAPHICMANAGER;
}