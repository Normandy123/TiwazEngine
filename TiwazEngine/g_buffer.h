#pragma once

#include <cstdint>

#include <array>

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

		GBuffer();
		~GBuffer();

		bool Init(const uint16_t & screen_width, const uint16_t & screen_height);

		void BindForWriting();
		void BindForReading();

	private:
		GLuint m_fbo;
		GLuint m_depth_texture;

		std::array<GLuint, GBUFFER_NUM_TEXTURES> m_textures;
	};
}