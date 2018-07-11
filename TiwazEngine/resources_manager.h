#pragma once

#include <cstdint>

#include <string>
#include <map>
#include <memory>

#include "binary_IO.h"

namespace Tiwaz::Resources
{
	const std::string meshes_path = "data/resources/meshes/";

	class MeshesIO
	{
	public:
		~MeshesIO()
		{
			m_loaded_meshes.clear();
		}

		void ReadMesh(const std::string & mesh_name)
		{
			if (!IsLoaded(mesh_name))
			{
				const std::string file_path = meshes_path + mesh_name + ".tbm";

				std::unique_ptr<FileFormats::MeshData> temp_mesh = std::unique_ptr<FileFormats::MeshData>();

				BinaryIO::ReadMesh(file_path, temp_mesh.get());

				m_loaded_meshes.insert(std::make_pair(mesh_name, std::move(temp_mesh)));
			}
		}

		void WriteMesh(const std::string & mesh_name, const FileFormats::MeshData * mesh_data)
		{
			const std::string file_path = meshes_path + mesh_name + ".tbm";

			if (IsLoaded(mesh_name))
			{
				//TODO: Write mesh when already loaded
			}
			
			BinaryIO::WriteMesh(file_path, mesh_data);
		}

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

	private:
		
	};
}