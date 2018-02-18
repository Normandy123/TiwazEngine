#pragma once

#include <vector>
#include <iostream>
#include <type_traits>

#define GLM_FORCE_SIZE_T_LENGTH
#include <GLM/glm.hpp>

#include "component.h"
#include "message_system.h"
#include "graphic_types.h"

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

	class GraphicComponent : public ComponentBase
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
		~MeshComponent()
		{
			if (m_mesh != nullptr)
			{
				delete m_mesh;
				m_mesh = nullptr;
			}
		}

		void SetMeshData(Graphic::Mesh* mesh) { m_mesh = mesh; }

		const std::vector<glm::vec3> Vertices() { return m_mesh->m_positions; }
		const std::vector<glm::vec3> Normals() { return m_mesh->m_normals; }
		const std::vector<glm::vec2> UVs() { return m_mesh->m_uvs; }

		const std::vector<unsigned int> Indices() { return m_mesh->m_indices; }
	private:
		Graphic::Mesh* m_mesh;
	};


	class ModelComponent : public GraphicComponent
	{
	public:
		ModelComponent()
		{
			Global::EVENTHANDLER->RegisterEventFunction(&ModelComponent::OnInit, this);
		}

		~ModelComponent()
		{
			Global::EVENTHANDLER->UnregisterEventFunction<EventSystem::ModelComponentInitEvent>(this);

			if (!m_meshes.empty())
			{
				for (Component<MeshComponent>* mesh_comp : m_meshes)
				{
					delete mesh_comp;
					mesh_comp = nullptr;
				}
			}

			m_meshes.clear();
		}

		void OnInit(const EventSystem::ModelComponentInitEvent* event)
		{
			//SetModelData(event->model);
		}

		void SetModelData(const uint64_t & model_ID)
		{
			/*
			Component<MeshComponent>* temp_mesh_comp;

			for (Graphic::Mesh* temp_mesh_data : model_data->m_meshes)
			{
				temp_mesh_comp = new Component<MeshComponent>();
				temp_mesh_comp->ptr()->SetMeshData(temp_mesh_data);

				m_meshes.push_back(temp_mesh_comp);

				temp_mesh_comp = nullptr;
			}
			*/
		}

		const std::vector<Component<MeshComponent>*> MeshComponents() { return m_meshes; }

	private:
		std::vector<Component<MeshComponent>*> m_meshes;

		uint64_t model_data_ID = 0;
	};
}