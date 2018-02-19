#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <GLM/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>

#include "counter.h"

namespace Tiwaz::Component
{
	class ModelComponent;
	class MeshComponent;
}

namespace Tiwaz::Loader
{
	struct MeshData
	{
		~MeshData()
		{
			m_positions.clear();
			m_normals.clear();
			m_uvs.clear();

			m_indices.clear();
		}

		std::string file_path = "";
		std::string m_name = "";
		uint64_t mesh_ID = 0;

		std::vector<glm::vec3> m_positions;
		std::vector<glm::vec3> m_normals;
		std::vector<glm::vec2> m_uvs;

		std::vector<unsigned int> m_indices;
	};

	struct ModelData
	{
		~ModelData()
		{
			m_meshes.clear();
		}

		std::string file_path = "";
		std::string name = "";
		uint64_t model_ID = 0;

		std::vector<MeshData*> m_meshes;
	};
}

namespace Tiwaz::Loader
{
	extern ModelData* LoadModel(const std::string & file_path);
}

namespace Tiwaz::Loader
{
	template<typename T> class ResourcesLoader
	{
	public:
		typedef T*(*LoadFunctionPointer)(const std::string &);

		ResourcesLoader(LoadFunctionPointer load_function)
		{
			m_load_function = load_function;
		}

		virtual ~ResourcesLoader()
		{
			for (auto pair : m_resources_map)
			{
				delete pair.second;
				pair.second = nullptr;
			}

			m_resources_map.clear();
			m_loaded_files_map.clear();
		}

		const uint64_t AddResource(const std::string & file_path)
		{
			bool found_path = false;

			for (auto pair : m_loaded_files_map)
			{
				if (pair.second == file_path)
				{
					found_path = true;
					break;
				}
			}

			if (!found_path && file_path != "")
			{
				uint64_t new_ID = m_ID_counter.NewID();

				m_resources_map.insert(std::make_pair(new_ID, (*m_load_function)(file_path)));
				m_loaded_files_map.insert(std::make_pair(new_ID, file_path));

				return new_ID;
			}

			return 0;
		}

		void RemoveResource(const uint64_t & ID)
		{
			if (m_resources_map.find(ID) != m_resources_map.cend())
			{
				m_loaded_files_map.erase(ID);

				delete m_resources_map[ID];
				m_resources_map[ID] = nullptr;

				m_resources_map.erase(ID);	
			}
		}

		T* AccessResource(const uint64_t & ID)
		{
			if (m_resources_map.find(ID) != m_resources_map.cend())
			{
				return m_resources_map[ID];
			}

			return nullptr;
		}

	protected:
		LoadFunctionPointer m_load_function;

		std::map<uint64_t, T*> m_resources_map;
		std::map<uint64_t, std::string> m_loaded_files_map;
		Counter::IDCounter m_ID_counter;
	};

	class ModelLoader : public ResourcesLoader<ModelData>
	{
	public:
		ModelLoader() : ResourcesLoader(&LoadModel)
		{

		}

		const uint64_t AddResource(const std::string & file_path)
		{
			const uint64_t temp_ID = this->ResourcesLoader<ModelData>::AddResource(file_path);

			m_resources_map[temp_ID]->model_ID = temp_ID;

			return temp_ID;
		}
	};
}

namespace Tiwaz::Global
{
	extern Loader::ModelLoader* MODELLOADER;
}