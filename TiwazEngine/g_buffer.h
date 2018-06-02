#pragma once

#include <cstdint>

#include <GLEW/glew.h>

#include "log_system.h"

namespace Tiwaz::Graphic
{
	template<typename T> size_t ARRAY_SIZE_IN_ELEMENTS_SIZE_T(T input_array[])
	{
		return sizeof(input_array) / sizeof(T);
	}

	template<typename T> GLsizei ARRAY_SIZE_IN_ELEMENTS_GLSIZEI(T input_array[])
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

		void Init(const GLsizei & screen_width, const GLsizei & screen_height);
		void Resize(const GLsizei & screen_width, const GLsizei & screen_height);

		void BindForWriting();
		void BindForReading();
		void SetReadBuffer(GBUFFER_TEXTURE_TYPE texture_type);
		void Unbind();

	private:
		GLuint m_fbo;
		GLuint m_depth_texture;

		GLuint m_textures[GBUFFER_NUM_TEXTURES];

		bool m_is_init = false;
	};
}