#pragma once

#include <cstdint>

#include <string>
#include <array>
#include <tuple>
#include <map>
#include <memory>

#include "file_IO.h"

namespace Tiwaz::Resources
{
	enum ResourcesTypes : uint8_t
	{
		MESH,
		SIZE_RESOURCES_TYPES
	};

	static const std::array<const std::string, SIZE_RESOURCES_TYPES> ResourcesPaths =
	{
		"data/resources/meshes/"
	};

	static const std::array<const std::string, SIZE_RESOURCES_TYPES> ResourcesExtensions =
	{
		".tbm"
	};

	class ResourcesManager
	{
	public:
		template<ResourcesTypes TResourceEnum> void ReadResource(const std::string & file_name)
		{
			if (!IsLoaded<TResourceEnum>(file_name))
			{
				const std::string file_path = ResourcesPaths[TResourceEnum] + file_name + ResourcesExtensions[TResourceEnum];

				auto & temp_map = std::get<TResourceEnum>(m_loaded_resources);

				auto temp_pointer = CreateResource(temp_map);
	
				ReadFile(file_path, temp_pointer.get());

				temp_map.insert(std::make_pair(file_name, std::move(temp_pointer)));
			}
		}

		template<ResourcesTypes TResourceEnum, typename T> void WriteResources(const std::string & file_name, T * data)
		{
			const std::string file_path = ResourcesPaths[TResourceEnum] + file_name + ResourcesExtensions[TResourceEnum];

			if (IsLoaded<TResourceEnum>(file_name))
			{
				WriteFile(file_path, data);

				ReadFile(file_path, std::get<TResourceEnum>(m_loaded_resources)[file_name].get());
			}
			else
			{
				WriteFile(file_path, data);
			}
		}

		template<ResourcesTypes TResourceEnum> const bool IsLoaded(const std::string & file_name)
		{
			return FindFileName(file_name, std::get<TResourceEnum>(m_loaded_resources));
		}

	private:
		template<typename T> std::unique_ptr<T> CreateResource(const std::map<std::string, std::shared_ptr<T>> & map)
		{
			return std::make_unique<T>();
		}

		//Read specialization
		template<typename T> void ReadFile(const std::string & file_path, T * data) = delete;

		template<> void ReadFile(const std::string & file_path, FileFormats::MeshData * data)
		{
			FileIO::ReadMesh(file_path, data);
		}

		//Write specialization
		template<typename T> void WriteFile(const std::string & file_path, T * data) = delete;

		template<> void WriteFile(const std::string & file_path, FileFormats::MeshData * data)
		{
			FileIO::WriteMesh(file_path, data);
		}

		template<typename T> const bool FindFileName(const std::string & file_name, const std::map<std::string, std::shared_ptr<T>> & map)
		{
			if (map.find(file_name) != map.cend())
			{
				return true;
			}

			return false;
		}

		std::tuple<
			std::map<std::string, std::shared_ptr<FileFormats::MeshData>>
		> m_loaded_resources;
	};
}