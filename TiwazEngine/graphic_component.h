#pragma once

#include <vector>
#include <iostream>
#include <type_traits>

#include <GLM/glm.hpp>

#include "component.h"
#include "render_scene.h"
#include "file_formats.h"
#include "resources_IO.h"

namespace Tiwaz::Graphic
{
	class MeshesManager;
}

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

	class MeshInstanceComponent : public GraphicComponent
	{
	public:
		~MeshInstanceComponent()
		{
			m_mesh_ID = 0;
			m_mesh_resource_ID = 0;
		}

		const uint64_t LoadMeshFromFile(const std::string & file_path)
		{
			if (!Global::MESHES_RESOURCES_MANAGER->HasLoad(file_path))
			{
				m_mesh_resource_ID = Global::MESHES_RESOURCES_MANAGER->ReadAndAddResource(file_path);

				return m_mesh_resource_ID;
			}
			else
			{
				m_mesh_resource_ID = Global::MESHES_RESOURCES_MANAGER->IDByFilePath(file_path);

				return m_mesh_resource_ID;
			}

			return 0;
		}

		//void SetMeshID(const uint64_t & ID) {}

		const uint64_t MeshID() { return m_mesh_ID; }
		const uint64_t MeshResourceID() { return m_mesh_resource_ID; }

	private:
		uint64_t m_mesh_ID = 0;
		uint64_t m_mesh_resource_ID = 0;
	};
}