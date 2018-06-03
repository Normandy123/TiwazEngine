#pragma once

#include <cstdint>

#include <string>
#include <vector>

#include <GLEW/glew.h>
#include <GLM/glm.hpp>

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

	class VerticesBuffer
	{
	public:
		VerticesBuffer();
		~VerticesBuffer();

		void Init();
	private:
		GLuint m_vbos[3];
		GLuint m_ebo = 0;

		GLuint m_vao = 0;
	};
}
