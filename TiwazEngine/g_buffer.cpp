#include "g_buffer.h"

bool Tiwaz::Graphic::GBuffer::Init(const uint16_t & screen_width, const uint16_t & screen_height)
{
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

	glGenTextures(static_cast<GLsizei>(m_textures.size()), m_textures.data());
	glGenTextures(1, &m_depth_texture);

	for (unsigned int i = 0; i < static_cast<GLsizei>(m_textures.size()); ++i)
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
	glDrawBuffers(static_cast<GLsizei>(m_textures.size()), DrawBuffers);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE)
	{
		Log(LogSystem::TIWAZ_ERROR, "GRPAHIC", "Could not intialize framebuffer!");
		return false;
	}

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	return true;
}
