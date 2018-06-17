#pragma once

#include <GLEW/glew.h>
#include <GLM/glm.hpp>

namespace Tiwaz::Graphic
{
	template<typename T> GLsizei ARRAY_SIZE_IN_ELEMENTS_GLSIZEI(T input_array[])
	{
		return static_cast<GLsizei>(sizeof(input_array) / sizeof(T));
	}

	class MeshBuffer
	{
	public:
		~MeshBuffer();

		void Init();
		void Update();
		void Exit();

	private:
		GLuint m_vao;

		GLuint m_vbos[3];

		GLuint m_ebo;
		GLuint m_tbo;
	};
}