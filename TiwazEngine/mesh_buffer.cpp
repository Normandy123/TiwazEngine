#include "mesh_buffer.h"

namespace Tiwaz::Global
{
	Graphic::TransformationsManager* TRANSFORMATION_MANAGER;
	Graphic::MeshesManager* MESHES_MANAGER;
}

namespace Tiwaz::Graphic
{
	MeshesBuffer::~MeshesBuffer()
	{
		for (std::pair<uint64_t, InstancedMesh*> instance : m_instances_map)
		{
			delete instance.second;
		}

		m_instances_map.clear();
	}

	void MeshesBuffer::AddMesh(const uint64_t & mesh_ID, const uint64_t & transformation_ID)
	{
		if (mesh_ID != 0 && transformation_ID != 0)
		{
			for (std::pair<uint64_t, InstancedMesh*> pair : m_instances_map)
			{
				if (pair.second->mesh_ID == mesh_ID)
				{
					const std::vector<uint64_t>::iterator transformation_it = std::find(pair.second->transformation_IDs.begin(), pair.second->transformation_IDs.end(), transformation_ID);

					if (transformation_it == pair.second->transformation_IDs.cend())
					{
						pair.second->transformation_IDs.push_back(transformation_ID);

						//const glm::mat4 temp_transformation = Global::TRANSFORMATION_MANAGER->Transformation(transformation_ID);
						//TODO: update transformation by IDs
					}

					break;
				}
				else
				{
					const uint64_t new_ID = m_ID_counter.NewID();

					InstancedMesh* temp_instance = new InstancedMesh;
					temp_instance->mesh_ID = mesh_ID;
					temp_instance->transformation_IDs.push_back(transformation_ID);

					//TODO: load vertices and transformation by IDs
					//const DataFormats::VerticesData temp_vertices = Global::MESHES_MANAGER->Vertices(mesh_ID);
					//const glm::mat4 temp_transformation = Global::TRANSFORMATION_MANAGER->Transformation(transformation_ID);

					m_instances_map.insert(std::make_pair(new_ID, temp_instance));

					temp_instance = nullptr;
				}
			}
		}
	}
}