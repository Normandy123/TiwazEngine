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
#include "file_formats.h"
#include "binary_IO.h"

namespace Tiwaz::Loader
{
	extern ResourcesFileFormats::ModelData* LoadModel(const std::string & file_path);
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

			if (file_path != "" && file_path != "UNDEFINED")
			{
				for (auto pair : m_loaded_files_map)
				{
					if (pair.second == file_path)
					{
						found_path = true;
						break;
					}
				}

				if (!found_path)
				{
					uint64_t new_ID = m_ID_counter.NewID();

					m_resources_map.insert(std::make_pair(new_ID, (*m_load_function)(file_path)));
					m_loaded_files_map.insert(std::make_pair(new_ID, file_path));

					return new_ID;
				}
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
}