#pragma once

#include <cstdint>

#include <string>
#include <vector>

#include <GLEW/glew.h>
#include <GLM/glm.hpp>

#include "graphic_component.h"
#include "graphic_data_formats.h"

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

		const uint64_t AddMesh(Component::MeshComponent* mesh);

	private:
		GLuint m_vao;

		GLuint m_vbos[3];

		GLuint m_ebo;
		GLuint m_tbo;

		std::vector<Component::MeshComponent*> m_mesh_components;
	};
}