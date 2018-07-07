#pragma once

#include <string>
#include <vector>
#include <map>

#include "counter.h"
#include "file_formats.h"
#include "binary_IO.h"

namespace Tiwaz::ResourcesIO
{
	template<typename TResource> class ResourcesManager
	{
	protected:
		struct MapValue
		{
			explicit MapValue(const std::string & file_path, TResource* resource)
			{
				m_resource = resource;
				m_file_path = file_path;
			}

			~MapValue()
			{
				m_file_path.clear();

				delete m_resource;
				m_resource = nullptr;
			}

			TResource* m_resource;
			std::string m_file_path;
		};

	public:
		typedef void(*ReadFunctionPointer)(const std::string &, TResource*);
		typedef void(*WriteFunctionPointer)(const std::string &, const TResource*);

		explicit ResourcesManager(ReadFunctionPointer read_function)
		{
			m_read_function = read_function;
		}

		ResourcesManager(ReadFunctionPointer read_function, WriteFunctionPointer write_function)
		{
			m_write_function = write_function;
			m_read_function = read_function;
		}

		virtual ~ResourcesManager()
		{
			for (std::pair<uint64_t, MapValue*> pair : m_resources_map)
			{
				delete pair.second;
			}

			m_resources_map.clear();
		}

		const uint64_t ReadAndAddResource(const std::string & file_path)
		{
			if (!HasLoad(file_path))
			{
				uint64_t new_ID = m_ID_counter.NewID();
			
				TResource* temp_resource = new TResource;
				(*m_read_function)(file_path, temp_resource);
			
				MapValue* temp_value = new MapValue(file_path, temp_resource);
			
				m_resources_map.insert(std::make_pair(new_ID, temp_value));
			
				temp_resource = nullptr;
				temp_value = nullptr;
			
				return new_ID;
			}

			return 0;
		}

		void RemoveResource(const uint64_t & ID)
		{
			if (ValidID(ID))
			{
				m_ID_counter.ReleaseID(ID);

				delete m_resources_map[ID];

				m_resources_map.erase(ID);
			}
		}

		const bool ValidID(const uint64_t & ID)
		{
			if (ID != 0)
			{
				if (m_resources_map.find(ID) != m_resources_map.cend())
				{
					return true;
				}
			}

			return false;
		}

		const bool HasLoad(const std::string & file_path)
		{
			if (file_path != "" && file_path != "UNDEFINED")
			{
				for (std::pair<uint64_t, MapValue*> pair : m_resources_map)
				{
					if (pair.second->m_file_path == file_path)
					{
						return true;
					}
				}
			}

			return false;
		}

		const uint64_t IDByFilePath(const std::string & file_path)
		{
			if (HasLoad(file_path))
			{
				for (std::pair<uint64_t, MapValue*> pair : m_resources_map)
				{
					if (pair.second->m_file_path == file_path)
					{
						return pair.first;
					}
				}
			}

			return 0;
		}

		const std::string FilePathByID(const uint64_t & ID)
		{
			if (ValidID(ID))
			{
				return m_resources_map[ID]->m_file_path;
			}

			return "UNDEFINED";
		}

		TResource* AccessResource(const uint64_t & ID)
		{
			if (ID != 0)
			{
				if (m_resources_map.find(ID) != m_resources_map.cend())
				{
					return m_resources_map[ID]->m_resource;
				}
			}

			return nullptr;
		}

		TResource* AccessResource(const std::string & file_path)
		{
			if (file_path != "" && file_path != "UNDEFINED")
			{
				for (std::pair<uint64_t, MapValue*> pair : m_resources_map)
				{
					if (pair.second->m_file_path == file_path)
					{
						return pair.second->m_resource;
					}
				}
			}

			return nullptr;
		}

	protected:
		ReadFunctionPointer m_read_function = nullptr;
		WriteFunctionPointer m_write_function = nullptr;
		
		std::map<uint64_t, MapValue*> m_resources_map;
		Counter::IDCounter m_ID_counter;	
	};

	class MeshesResourcesManager : public ResourcesManager<FileFormats::MeshData>
	{
	public:
		explicit MeshesResourcesManager() : ResourcesManager(&BinaryIO::ReadMesh, &BinaryIO::WriteMesh) {}
	};
}

namespace Tiwaz::Global
{
	extern ResourcesIO::MeshesResourcesManager* MESHES_RESOURCES_MANAGER;
}