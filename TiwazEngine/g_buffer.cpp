#include "g_buffer.h"

Tiwaz::Graphic::GBuffer::~GBuffer()
{
	m_is_init = false;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &m_fbo);

	for (size_t i = 0; i < GBUFFER_NUM_TEXTURES; ++i)
	{
		if (m_textures[i] != 0)
		{
			glDeleteTextures(1, &m_textures[i]);
		}
	}

	glDeleteTextures(static_cast<GLsizei>(GBUFFER_NUM_TEXTURES), m_textures);
	glDeleteTextures(1, &m_depth_texture);
}

void Tiwaz::Graphic::GBuffer::Init(const GLsizei & screen_width, const GLsizei & screen_height)
{
	glGenTextures(static_cast<GLsizei>(GBUFFER_NUM_TEXTURES), m_textures);
		
	glGenTextures(1, &m_depth_texture);

	for (int i = 0; i < GBUFFER_NUM_TEXTURES; ++i)
	{
		glBindTexture(GL_TEXTURE_2D, m_textures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, screen_width, screen_height,
			0, GL_RGB, GL_FLOAT, nullptr);
	}

	glBindTexture(GL_TEXTURE_2D, m_depth_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, screen_width, screen_height,
		0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textures[0], 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_textures[1], 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_textures[2], 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, m_textures[3], 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_texture, 0);

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(static_cast<GLsizei>(GBUFFER_NUM_TEXTURES), DrawBuffers);

	GLenum framebuffer_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (framebuffer_status != GL_FRAMEBUFFER_COMPLETE)
	{
		Log(LogSystem::TIWAZ_ERROR, "GRAPHIC", "Could not intialize framebuffer!");
	}
	else
	{
		m_is_init = true;
	}

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void Tiwaz::Graphic::GBuffer::Resize(const GLsizei & screen_width, const GLsizei & screen_height)
{
	if (m_is_init)
	{
		for (int i = 0; i < GBUFFER_NUM_TEXTURES; ++i)
		{
			glBindTexture(GL_TEXTURE_2D, m_textures[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, screen_width, screen_height,
				0, GL_RGB, GL_FLOAT, nullptr);
		}

		glBindTexture(GL_TEXTURE_2D, m_depth_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, screen_width, screen_height,
			0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
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

void Tiwaz::Graphic::GBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}