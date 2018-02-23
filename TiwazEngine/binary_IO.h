#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "file_types.h"

namespace Tiwaz::IO
{
	static char* ToCharPointer(float value)
	{
		char char_float[4];
		memcpy(char_float, &value, 4);

		return char_float;
	}

	template<typename T> static void WriteValueToStream(std::ofstream & stream, T data)
	{
		stream.write(reinterpret_cast<char*>(&data), sizeof(T));
	}

	template<typename T> static void WriteVectorToStream(std::ofstream & stream, std::vector<T> vector)
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

		temp_char_vector.clear();
	}

	template<> static void WriteVectorToStream(std::ofstream & stream, std::vector<glm::vec2> vector)
	{
		std::streamsize value_stream_size = sizeof(float);

		std::vector<char*> temp_char_vector;

		for (glm::vec2 value : vector)
		{
			temp_char_vector.push_back(ToCharPointer(value.x));
			temp_char_vector.push_back(ToCharPointer(value.y));
		}

		for (char* value : temp_char_vector)
		{
			stream.write(value, value_stream_size);
		}

		temp_char_vector.clear();
	}

	template<> static void WriteVectorToStream(std::ofstream & stream, std::vector<glm::vec3> vector)
	{
		std::streamsize value_stream_size = sizeof(float);

		std::vector<char*> temp_char_vector;

		for (glm::vec3 value : vector)
		{
			temp_char_vector.push_back(ToCharPointer(value.x));
			temp_char_vector.push_back(ToCharPointer(value.y));
			temp_char_vector.push_back(ToCharPointer(value.z));
		}

		for (char* value : temp_char_vector)
		{
			stream.write(value, value_stream_size);
		}

		temp_char_vector.clear();
	}

	static void WriteMesh(std::ofstream & stream, const FileFormats::MeshData & mesh)
	{
		WriteValueToStream(stream, mesh.mesh_name); 
		WriteValueToStream(stream, mesh.size_positions); WriteValueToStream(stream, mesh.size_normals); WriteValueToStream(stream, mesh.size_uvs);
		WriteValueToStream(stream, 0xffff);
		WriteVectorToStream(stream, mesh.positions); WriteVectorToStream(stream, mesh.normals); WriteVectorToStream(stream, mesh.uvs);
	}

	class BinaryIO
	{
	public:

	private:
		std::fstream m_file_stream;
	};
}