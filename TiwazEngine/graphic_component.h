#pragma once

#include <vector>
#include <iostream>
#include <type_traits>

#include <GLM/glm.hpp>

#include "component.h"
#include "file_formats.h"
#include "resources_IO.h"
#include "render_scene.h"

namespace Tiwaz::Component
{
	class GraphicComponent : public ComponentBase
	{
	public:
		GraphicComponent()
		{
			Global::RENDER_SCENE->AddComponent(this);
		}

		virtual ~GraphicComponent()
		{
			Global::RENDER_SCENE->RemoveComponent(this);
		}
	};

	class MeshComponent : public GraphicComponent
	{
	public:
		~MeshComponent()
		{
			m_mesh_ID = 0;
		}

		void LoadAndSetMesh(const std::string & file_path)
		{
			m_mesh_ID = Global::MESH_RESOURCES_MANAGER->ReadAndAddResource(file_path);
		}

		void SetMesh(const uint64_t & ID)
		{
			if (Global::MESH_RESOURCES_MANAGER->ValidID(ID))
			{
				m_mesh_ID = ID;
			}		
		}

		const uint64_t MeshID()
		{
			return m_mesh_ID;
		}

		FileFormats::MeshData* AccessMesh()
		{
			return Global::MESH_RESOURCES_MANAGER->AccessResource(m_mesh_ID);
		}

	private:
		uint64_t m_mesh_ID = 0;
	};
}