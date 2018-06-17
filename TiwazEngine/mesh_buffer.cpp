#include "mesh_buffer.h"

Tiwaz::Graphic::MeshBuffer::~MeshBuffer()
{
	glBindVertexArray(0);

	glDeleteBuffers(3, m_vbos);
	glDeleteBuffers(1, &m_ebo);
	glDeleteBuffers(1, &m_tbo);

	glDeleteVertexArrays(1, &m_vao);
}

void Tiwaz::Graphic::MeshBuffer::Init()
{
	glCreateVertexArrays(1, &m_vao);

	glCreateBuffers(3, m_vbos);
	glCreateBuffers(1, &m_ebo);
	glCreateBuffers(1, &m_tbo);
}
