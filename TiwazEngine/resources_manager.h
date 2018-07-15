#pragma once

#include <cstdint>

#include <string>
#include <array>
#include <map>
#include <memory>
#include <iostream>

#include "file_IO.h"

namespace Tiwaz::Resources
{
	enum ResourcesTypes : uint8_t
	{
		TEXTURE,
		MESH,

		AUDIOCLIP,

		SIZE_RESOURCES_TYPES
	};

	static const std::array<const std::string, SIZE_RESOURCES_TYPES> ResourcesPaths =
	{
		"",
		"data/resources/meshes/",
		""
	};

	static const std::array<const std::string, SIZE_RESOURCES_TYPES> ResourcesExtensions =
	{
		"",
		".tbm",
		""
	};

	class MeshesIO
	{
	public:
		~MeshesIO()
		{
			m_loaded_meshes.clear();
		}

		/*
		void ReadMesh(const std::string & mesh_name)
		{
			if (!IsLoaded(mesh_name))
			{
				const std::string file_path = meshes_path + mesh_name + ".tbm";

				std::unique_ptr<FileFormats::MeshData> temp_mesh = std::unique_ptr<FileFormats::MeshData>();

				FileIO::ReadMesh(file_path, temp_mesh.get());

				m_loaded_meshes.insert(std::make_pair(mesh_name, std::move(temp_mesh)));
			}
		}

		void WriteMesh(const std::string & mesh_name, const FileFormats::MeshData * mesh_data)
		{
			const std::string file_path = meshes_path + mesh_name + ".tbm";

			if (IsLoaded(mesh_name))
			{
				FileIO::WriteMesh(file_path, mesh_data);

				FileIO::ReadMesh(file_path, m_loaded_meshes[mesh_name].get());
			}
			
			FileIO::WriteMesh(file_path, mesh_data);
		}
		*/

		const bool IsLoaded(const std::string & mesh_name)
		{
			if (m_loaded_meshes.find(mesh_name) != m_loaded_meshes.cend())
			{
				return true;
			}

			return false;
		}

		std::shared_ptr<FileFormats::MeshData> AccessMesh(const std::string & mesh_name)
		{
			if (IsLoaded(mesh_name))
			{
				return m_loaded_meshes[mesh_name];
			}

			return nullptr;
		}
	private:
		std::map<std::string, std::shared_ptr<FileFormats::MeshData>> m_loaded_meshes;
	};

	//TODO: implement ResourcesManager
	class ResourcesManager
	{
	public:
		template<ResourcesTypes TResourceEnum> void ReadFile(const std::string & file_name);

		template<> void ReadFile<MESH>(const std::string & file_name)
		{
			if (!IsLoaded<MESH>(file_name))
			{
				const std::string file_path = ResourcesPaths[MESH] + file_name + ResourcesExtensions[MESH];

				std::unique_ptr<FileFormats::MeshData> temp_mesh = std::unique_ptr<FileFormats::MeshData>();

				FileIO::ReadMesh(file_path, temp_mesh.get());

				m_loaded_meshes.insert(std::make_pair(file_name, std::move(temp_mesh)));
			}
		}

		template<typename T> const bool FindFileName(const std::string & file_name, const std::map<std::string, std::shared_ptr<T>> & map)
		{
			if (map.find(file_name) != map.cend())
			{
				return true;
			}

			return false;
		}

		template<ResourcesTypes TResourceEnum> const bool IsLoaded(const std::string & file_name);

		template<> const bool IsLoaded<MESH>(const std::string & file_name)
		{
			return FindFileName<FileFormats::MeshData>(file_name, m_loaded_meshes);
		}

	private:
		std::map<std::string, std::shared_ptr<FileFormats::MeshData>> m_loaded_meshes;
	};
}