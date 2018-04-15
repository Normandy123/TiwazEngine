#include "graphic_system.h"

#include "main_renderer.h"

namespace Tiwaz::Graphic
{
	GraphicManager::GraphicManager()
	{
		Global::ENGINE_EVENT_HANDLER->RegisterEventFunction(&GraphicManager::OnScreenShow, this);
		Global::ENGINE_EVENT_HANDLER->RegisterEventFunction(&GraphicManager::OnScreenResize, this);
	}

	GraphicManager::~GraphicManager()
	{
		Global::ENGINE_EVENT_HANDLER->UnregisterEventFunction<EventSystem::ScreenShowEvent>(this);
		Global::ENGINE_EVENT_HANDLER->UnregisterEventFunction<EventSystem::ScreenResizeEvent>(this);
	}
	
	void GraphicManager::Init()
	{
		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK)
		{
			Log(LogSystem::TIWAZ_FATALERROR, "GRPAHIC", "Could not intialize GLEW!");
		}

		glClearColor(0.2f, 0.5f, 0.7f, 1.0f);

		Global::MAIN_RENDERER->Init();
	}

	void GraphicManager::Update()
	{
		Global::MAIN_RENDERER->Update();
	}

	void GraphicManager::Render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glVertex3f(-0.5, 0.0, 0.0);
		glVertex3f(0.0, 0.5, 0.0);
		glVertex3f(0.5, 0.0, 0.0);
		glEnd();

		Global::MAIN_RENDERER->Render();
	}

	void GraphicManager::Exit()
	{
		Global::MAIN_RENDERER->Exit();
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
	Graphic::GraphicManager* GRAPHIC_MANAGER;
}