#include "main_renderer.h"

#include "graphic_system.h"

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
	m_gbuffer.Init(static_cast<GLsizei>(Global::GRAPHIC_MANAGER->ScreenWidth()), static_cast<GLsizei>(Global::GRAPHIC_MANAGER->ScreenHeight()));
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

}

void Tiwaz::Graphic::MainRenderer::OnScreenResize(const EventSystem::ScreenResizeEvent * event)
{
	m_gbuffer.Resize(static_cast<GLsizei>(event->width), static_cast<GLsizei>(event->height));

	m_width = static_cast<GLint>(event->width); m_height = static_cast<GLint>(event->height);
	m_half_width = static_cast<GLint>(std::floor(m_width / 2.0f)); m_half_height = static_cast<GLuint>(std::floor(m_height / 2.0f));
}

void Tiwaz::Graphic::MainRenderer::GeometryPass()
{
	m_gbuffer.BindForWriting();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Tiwaz::Graphic::MainRenderer::LightPass()
{
	m_gbuffer.Unbind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_gbuffer.BindForReading();

	m_gbuffer.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
	glBlitFramebuffer(0, 0, m_width, m_height,
		0, 0, m_half_width, m_half_height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	m_gbuffer.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
	glBlitFramebuffer(0, 0, m_width, m_height,
		0, m_half_height, m_half_width, m_height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	m_gbuffer.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
	glBlitFramebuffer(0, 0, m_width, m_height,
		m_half_width, m_half_height, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	m_gbuffer.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_TEXCOORD);
	glBlitFramebuffer(0, 0, m_width, m_height,
		m_half_width, 0, m_width, m_half_height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}