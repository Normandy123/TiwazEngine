#pragma once

#include <vector>
#include <iostream>

#define GLM_FORCE_SIZE_T_LENGTH
#include <GLM/glm.hpp>

#include "component.h"

namespace Tiwaz::Component
{
	typedef std::vector<float> vec;

	template<typename T> vec GlmVecToVec(const T & glm_vec)
	{
		const size_t len = glm_vec.length();
		
		vec temp_vec(len);
		
		for (size_t i = 0; i < len; i++)
		{
			temp_vec[i] = glm_vec[i];
		}

	}

	template<typename T> std::vector<vec> VecGlmVecToVecVec(const std::vector<T> vec_glm_vec)
	{
		const size_t len = vec_glm_vec.size();

		std::vector<vec> temp_vec(len);

		for (size_t i = 0; i < len; i++)
		{
			temp_vec[i] = GlmVecToVec(vec_glm_vec[i]);
		}

		return temp_vec;
	}
	
	/*
	vec GlmVec3ToVec3(const glm::vec3 & glm_vec3)
	{
		vec temp_vec(3);

		for (size_t i = 0; i < 3; i++)
		{
			temp_vec[i] = glm_vec3[i];
		}

		return temp_vec;
	}
	*/

	class GraphicComponent : public Component
	{

	};

	class MeshComponent : public GraphicComponent
	{
	public:
		MeshComponent()
		{

		}

		~MeshComponent()
		{
			m_vertices.clear();
			m_normals.clear();
			m_uvs.clear();
		}

		inline const std::vector<vec> Vertices() { return VecGlmVecToVecVec(m_vertices); }
		inline const std::vector<vec> Normals() { return VecGlmVecToVecVec(m_normals); }
		inline const std::vector<vec> UVs() { return VecGlmVecToVecVec(m_uvs); }
	private:
		std::vector<glm::vec3> m_vertices = std::vector<glm::vec3>();
		std::vector<glm::vec3> m_normals = std::vector<glm::vec3>();
		std::vector<glm::vec2> m_uvs = std::vector<glm::vec2>();
	};

	class ModelComponent : public GraphicComponent
	{

	};
}