#pragma once

#include <cstdint>

#include <GLEW/glew.h>

#include "log_system.h"

namespace Tiwaz::Graphic
{
	class GBuffer
	{
	public:
		enum GBUFFER_TEXTURE_TYPE
		{
			GBUFFER_TEXTURE_TYPE_POSITION,
			GBUFFER_TEXTURE_TYPE_DIFFUSE,
			GBUFFER_TEXTURE_TYPE_NORMAL,
			GBUFFER_TEXTURE_TYPE_TEXCOORD,
			GBUFFER_NUM_TEXTURES
		};

		~GBuffer();

		void Init(const GLsizei & screen_width, const GLsizei & screen_height);
		void Resize(const GLsizei & screen_width, const GLsizei & screen_height);

		void BindForWriting();
		void BindForReading();
		void SetReadBuffer(GBUFFER_TEXTURE_TYPE texture_type);
		void Unbind();

	private:
		GLuint m_fbo = 0;
		GLuint m_depth_texture = 0;

		GLuint m_textures[GBUFFER_NUM_TEXTURES] = {0};

		bool m_is_init = false;
	};
}