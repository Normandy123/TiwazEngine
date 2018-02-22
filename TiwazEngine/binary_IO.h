#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "file_types.h"

namespace Tiwaz::IO
{
	template<typename T> void WriteValueToStream(std::ofstream & stream, T data)
	{
		stream.write(reinterpret_cast<char*>(&data), sizeof(T));
	}

	template<typename T> void WriteVectorToStream(std::ofstream & stream, std::vector<T> vector)
	{
		std::streamsize value_stream_size = sizeof(T);
		
		std::vector<char*> temp_char_vector;

		for (T value : vector)
		{
			temp_char_vector.push_back(reinterpret_cast<char*>(value));
		}

		for (char* value : temp_char_vector)
		{
			stream.write(value, value_stream_size);
		}
	}

	template<> void WriteVectorToStream(std::ofstream & stream, std::vector<glm::vec3> vector)
	{
		std::streamsize value_stream_size = sizeof(float);

		std::vector<char*> temp_char_vector;

		for (glm::vec3 value : vector)
		{
			//TODO: float to char* convertions
			temp_char_vector.push_back(reinterpret_cast<char*>(value.x));
		}

		for (char* value : temp_char_vector)
		{
			stream.write(value, value_stream_size);
		}
	}

	static void WriteMesh(std::ofstream & stream, const FileFormats::MeshData & mesh)
	{
		WriteValueToStream(stream, mesh.mesh_name); 
		WriteValueToStream(stream, mesh.size_positions); WriteValueToStream(stream, mesh.size_normals); WriteValueToStream(stream, mesh.size_uvs);
		WriteVectorToStream(stream, mesh.positions); WriteVectorToStream(stream, mesh.normals); WriteVectorToStream(stream, mesh.uvs);
	}

	class BinaryIO
	{
	public:
		template<typename T> bool Write(const std::string & write_file_path, T data)
		{
			m_file_stream.open(write_file_path, std::ios::binary | std::ios::out);

			if (!m_file_stream.is_open())
			{
				return false;
			}

			m_file_stream.write(reinterpret_cast<char*>(&data), sizeof(T));

			m_file_stream.close();

			return true;
		}

		template<typename T> bool Read(const std::string & read_file_path, T object)
		{
			m_file_stream.open(read_file_path, std::ios::binary | std::ios::in);

			if (!m_file_stream.is_open())
			{
				return false;
			}

			m_file_stream.read(reinterpret_cast<char*>(&object), sizeof(T));

			m_file_stream.close();

			return true;
		}

	private:
		std::fstream m_file_stream;
	};
}