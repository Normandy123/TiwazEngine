#pragma once

#include <cstdint>

#include <string>
#include <array>
#include <map>
#include <memory>

#include "file_IO.h"

namespace Tiwaz::Resources
{
	enum RESOURCETYPE : uint8_t
	{
		MESH,
		SIZE_RESOURCE_TYPES
	};

	static const std::array<const std::string, SIZE_RESOURCE_TYPES> RESOURCEPATHS =
	{
		"data/resources/meshes/"
	};

	static const std::array<const std::string, SIZE_RESOURCE_TYPES> RESOURCEEXTENSIONS =
	{
		".tbm"
	};

	class ResourcesManager
	{
	public:
		const bool IsLoaded(const std::string & file_name, const RESOURCETYPE resource_type)
		{
			auto & temp_map = m_loaded_resources[resource_type];

			if (temp_map.find(file_name) != temp_map.cend())
			{
				return true;
			}

			return false;
		}

		

	private:

		std::array<std::map<std::string, std::shared_ptr<FileFormats::DataBase>>, SIZE_RESOURCE_TYPES> m_loaded_resources;
	};
}