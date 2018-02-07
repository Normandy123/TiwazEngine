#pragma once

#include <vector>
#include <iostream>
#include <type_traits>

#define GLM_FORCE_SIZE_T_LENGTH
#include <GLM/glm.hpp>

#include "component.h"
#include "render_scene.h"
#include "message_system.h"

namespace Tiwaz::Component
{
	typedef std::vector<float> vec;

	template<typename T> constexpr vec GlmVecToVec(T glm_vec)
	{
		if (std::is_same<T, glm::vec2>::value || std::is_same<T, glm::vec3>::value || std::is_same<T, glm::vec4>::value)
		{
			const size_t len = glm_vec.length();

			vec temp_vec(len);

			for (size_t i = 0; i < len; i++)
			{
				temp_vec[i] = glm_vec[i];
			}

			return temp_vec;
		}
		else
		{
			Message(MessageSystem::TIWAZ_WARNING, "Component", "Can only convert glm::vec to float vector!");
			vec temp = { 0, 0, 0 };

			return temp;
		}
	}

	template<typename T> constexpr std::vector<vec> VecGlmVecToVecVec(std::vector<T> vec_glm_vec)
	{
		const size_t len = vec_glm_vec.size();

		std::vector<vec> temp_vec(len);

		for (size_t i = 0; i < len; i++)
		{
			temp_vec[i] = GlmVecToVec(vec_glm_vec[i]);
		}

		return temp_vec;
	}

	class GraphicComponent : public Component
	{
	public:
		GraphicComponent()
		{

		}

		~GraphicComponent()
		{
			
		}
	};

	class MeshComponent : public GraphicComponent
	{
	public:
		MeshComponent()
		{
			m_vertices.emplace_back(2, 2, 2);
			m_vertices.emplace_back(2, 3, 1);
		}

		~MeshComponent()
		{
			m_vertices.clear();
			m_normals.clear();
			m_uvs.clear();
		}

		const std::vector<glm::vec3> Vertices() { return m_vertices; }
		const std::vector<glm::vec3> Normals() { return m_normals; }
		const std::vector<glm::vec2> UVs() { return m_uvs; }
	private:
		std::vector<glm::vec3> m_vertices;
		std::vector<glm::vec3> m_normals;
		std::vector<glm::vec2> m_uvs;
	};

	class ModelComponent : public GraphicComponent
	{
	public:
		ComponentContainer<MeshComponent> m_mesh;
	};
}