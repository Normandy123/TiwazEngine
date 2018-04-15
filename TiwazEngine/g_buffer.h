#pragma once

#include <cstdint>

#include <GLEW/glew.h>

#include "log_system.h"

namespace Tiwaz::Graphic
{
	template<typename T> GLsizei ARRAY_SIZE_IN_ELEMENTS(T input_array[])
	{
		return static_cast<GLsizei>(sizeof(input_array) / sizeof(T));
	}

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

		void Init(const uint16_t & screen_width, const uint16_t & screen_height);

		void BindForWriting();
		void BindForReading();
		void SetReadBuffer(GBUFFER_TEXTURE_TYPE texture_type);

	private:
		GLuint m_fbo;
		GLuint m_depth_texture;

		GLuint m_textures[GBUFFER_NUM_TEXTURES];
	};
}