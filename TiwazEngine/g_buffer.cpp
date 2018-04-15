#include "g_buffer.h"

Tiwaz::Graphic::GBuffer::~GBuffer()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &m_fbo);
}

void Tiwaz::Graphic::GBuffer::Init(const uint16_t & screen_width, const uint16_t & screen_height)
{
	if (m_fbo == 0)
	{
		glGenFramebuffers(1, &m_fbo);
	}

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

	bool textures_generated = true;

	for (GLuint i : m_textures)
	{
		if (i == 0)
		{
			textures_generated = false;
			break;
		}
	}

	if (!textures_generated)
	{
		glGenTextures(ARRAY_SIZE_IN_ELEMENTS(m_textures), m_textures);
	}

	if (m_depth_texture == 0)
	{
		glGenTextures(1, &m_depth_texture);
	}

	for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_textures); i++)
	{
		glBindTexture(GL_TEXTURE_2D, m_textures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, static_cast<GLsizei>(screen_width), static_cast<GLsizei>(screen_height),
			0, GL_RGB, GL_FLOAT, nullptr);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textures[i], 0);
	}

	glBindTexture(GL_TEXTURE_2D, m_depth_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, static_cast<GLsizei>(screen_width), static_cast<GLsizei>(screen_height),
		0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_texture, 0);

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(ARRAY_SIZE_IN_ELEMENTS(m_textures), DrawBuffers);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE)
	{
		Log(LogSystem::TIWAZ_ERROR, "GRPAHIC", "Could not intialize framebuffer!");
	}

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void Tiwaz::Graphic::GBuffer::BindForWriting()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
}

void Tiwaz::Graphic::GBuffer::BindForReading()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
}

void Tiwaz::Graphic::GBuffer::SetReadBuffer(GBUFFER_TEXTURE_TYPE texture_type)
{
	glReadBuffer(GL_COLOR_ATTACHMENT0 + texture_type);
}
