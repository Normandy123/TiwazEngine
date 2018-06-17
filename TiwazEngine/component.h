#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "constants.h"
#include "event_system.h"
#include "object_system.h"

namespace Tiwaz::Component
{
	class ComponentBase : public EngineObject
	{
	public:
		ComponentBase()
		{	
			Global::ENGINE_EVENT_HANDLER->RegisterEventFunction(&ComponentBase::OnInit, this);
			Global::ENGINE_EVENT_HANDLER->RegisterEventFunction(&ComponentBase::OnUpdate, this);
			Global::ENGINE_EVENT_HANDLER->RegisterEventFunction(&ComponentBase::OnExit, this);
		}

		virtual ~ComponentBase()
		{
			Global::ENGINE_EVENT_HANDLER->UnregisterEventFunction<EventSystem::ComponentInitEvent>(this);
			Global::ENGINE_EVENT_HANDLER->UnregisterEventFunction<EventSystem::ComponentUpdateEvent>(this);
			Global::ENGINE_EVENT_HANDLER->UnregisterEventFunction<EventSystem::ComponentExitEvent>(this);
		}

		virtual void OnInit(const EventSystem::ComponentInitEvent* event) {}
		virtual void OnUpdate(const EventSystem::ComponentUpdateEvent* event) {}
		virtual void OnExit(const EventSystem::ComponentExitEvent* event) {}
	};

	class TransformationComponent : public ComponentBase
	{
	public:
		TransformationComponent()
		{

		}

		virtual ~TransformationComponent()
		{

		}

		void OnUpdate(const EventSystem::ComponentUpdateEvent* event)
		{
			if (m_has_changed)
			{
				glm::scale(m_transformation, current_scale);

				glm::rotate(m_transformation, current_rotation.x, X_DIRECTION);
				glm::rotate(m_transformation, current_rotation.y, Y_DIRECTION);
				glm::rotate(m_transformation, current_rotation.z, Z_DIRECTION);

				glm::translate(m_transformation, current_translation);

				m_has_changed = false;
			}
		}

		void Translate(const float & x, const float & y, const float & z)
		{
			m_has_changed = true;

			current_translation = glm::vec3(x, y, z);
		}

		void Translate(const glm::vec3 & vec)
		{
			m_has_changed = true;

			current_translation = vec;
		}

		void Rotate(const float & x, const float & y, const float & z)
		{
			m_has_changed = true;

			const float x_rot = glm::radians(x);
			const float y_rot = glm::radians(y);
			const float z_rot = glm::radians(z);

			current_rotation = glm::vec3(x_rot, y_rot, z_rot);
		}

		void Rotate(const glm::vec3 & vec)
		{
			m_has_changed = true;

			const float x_rot = glm::radians(vec.x);
			const float y_rot = glm::radians(vec.y);
			const float z_rot = glm::radians(vec.z);

			current_rotation = glm::vec3(x_rot, y_rot, z_rot);
		}

		void Scale(const float & x, const float & y, const float & z)
		{
			m_has_changed = true;

			current_scale = glm::vec3(x, y, z);
		}

		void Scale(const glm::vec3 & vec)
		{
			m_has_changed = true;

			current_scale = vec;
		}

		glm::mat4 const * Transformation() { return std::addressof(m_transformation); }

	private:
		bool m_has_changed = false;

		glm::vec3 current_translation = glm::vec3(0.0f);
		glm::vec3 current_rotation = glm::vec3(0.0f);
		glm::vec3 current_scale = glm::vec3(1.0f);

		glm::mat4 m_transformation = glm::mat4(0.0f);
	};

	class CameraComponent : public ComponentBase
	{
	private:
		bool m_has_changed = false;

		glm::vec3 current_translation = glm::vec3(0.0f);
		glm::vec3 current_rotation = glm::vec3(0.0f);
		glm::vec3 current_scale = glm::vec3(1.0f);

		glm::mat4 m_transformation = glm::mat4(1.0f);
	};
}