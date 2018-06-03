#include "vertices_buffer.h"

namespace Tiwaz::Graphic
{
	VerticesBuffer::VerticesBuffer()
	{
	}

	VerticesBuffer::~VerticesBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(ARRAY_SIZE_IN_ELEMENTS_GLSIZEI(m_vbos), m_vbos);
		glDeleteBuffers(1, &m_ebo);

		glBindVertexArray(0);
		glDeleteVertexArrays(1, &m_vao);
	}

	void VerticesBuffer::Init()
	{
		glGenBuffers(ARRAY_SIZE_IN_ELEMENTS_GLSIZEI(m_vbos), m_vbos);
		glGenBuffers(1, &m_ebo);

		glGenVertexArrays(1, &m_vao);
	}
}