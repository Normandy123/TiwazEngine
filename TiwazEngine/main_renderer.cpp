#include "main_renderer.h"

namespace Tiwaz::Global
{
	Graphic::MainRenderer* MAIN_RENDERER;
}

Tiwaz::Graphic::MainRenderer::MainRenderer()
{
	Global::ENGINE_EVENT_HANDLER->RegisterEventFunction(&MainRenderer::OnScreenShow, this);
	Global::ENGINE_EVENT_HANDLER->RegisterEventFunction(&MainRenderer::OnScreenResize, this);
}

Tiwaz::Graphic::MainRenderer::~MainRenderer()
{
	Global::ENGINE_EVENT_HANDLER->UnregisterEventFunction<EventSystem::ScreenShowEvent>(this);
	Global::ENGINE_EVENT_HANDLER->UnregisterEventFunction<EventSystem::ScreenResizeEvent>(this);
}

void Tiwaz::Graphic::MainRenderer::Init()
{

}

void Tiwaz::Graphic::MainRenderer::Update()
{
}

void Tiwaz::Graphic::MainRenderer::Render()
{
	if (Global::RENDER_SCENE->HasComponents())
	{
		GeometryPass();
		LightPass();
	}
}

void Tiwaz::Graphic::MainRenderer::Exit()
{
}

void Tiwaz::Graphic::MainRenderer::OnScreenShow(const EventSystem::ScreenShowEvent * event)
{
	m_gbuffer.Init(event->width, event->height);
}

void Tiwaz::Graphic::MainRenderer::OnScreenResize(const EventSystem::ScreenResizeEvent * event)
{
	m_gbuffer.Init(event->width, event->height);
}

void Tiwaz::Graphic::MainRenderer::GeometryPass()
{
	
}

void Tiwaz::Graphic::MainRenderer::LightPass()
{

}