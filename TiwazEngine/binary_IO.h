#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "file_types.h"

namespace Tiwaz::IO
{
	template<typename T> static void WriteValueToStream(std::ofstream & stream, T data)
	{
		stream.write(reinterpret_cast<const char*>(&data), sizeof(T));
	}

	template<typename T> static void WriteValueToStream(std::ofstream & stream, std::string data)
	{
		stream.write(&data.c_str(), data.size());
	}

	template<typename T> static void WriteVectorToStream(std::ofstream & stream, std::vector<T> vector)
	{	
		const size_t value_size = sizeof(T);

		for (const T vector_value : vector)
		{
			stream.write(reinterpret_cast<const char*>(&vector_value), value_size);
		}
	}

	template<> static void WriteVectorToStream(std::ofstream & stream, std::vector<glm::vec2> vector)
	{
		const size_t value_size = sizeof(float);

		std::vector<float> float_buffer;

		for (const glm::vec2 vector_value : vector)
		{
			float_buffer.push_back(vector_value.x);
			float_buffer.push_back(vector_value.y);
		}

		for (const float vector_value : float_buffer)
		{
			stream.write(reinterpret_cast<const char*>(&vector_value), value_size);
		}

		float_buffer.clear();
	}

	template<> static void WriteVectorToStream(std::ofstream & stream, std::vector<glm::vec3> vector)
	{
		const size_t value_size = sizeof(float);

		std::vector<float> float_buffer;

		for (const glm::vec3 vector_value : vector)
		{
			float_buffer.push_back(vector_value.x);
			float_buffer.push_back(vector_value.y);
			float_buffer.push_back(vector_value.z);
		}

		for (const float vector_value : float_buffer)
		{
			stream.write(reinterpret_cast<const char*>(&vector_value), value_size);
		}

		float_buffer.clear();
	}

	template<typename T> static void ReadValueFromStream(std::ifstream & stream, T & data)
	{
		stream.read(reinterpret_cast<char*>(&data), sizeof(T));
	}

	template<typename T> static void ReadVectorFromStream(std::ifstream & stream, std::vector<T> & vector, const size_t & size)
	{
		const size_t value_size = sizeof(T);

		for (size_t i = 0; i < size; ++i)
		{
			T temp_value;

			stream.read(reinterpret_cast<char*>(&temp_value), value_size);

			vector.push_back(temp_value);
		}
	}

	template<> static void ReadVectorFromStream(std::ifstream & stream, std::vector<glm::vec2> & vector, const size_t & size)
	{
		std::vector<float> float_buffer;

		const size_t value_size = sizeof(float);

		for (size_t i = 0; i < size * 2; ++i)
		{
			float temp_value;

			stream.read(reinterpret_cast<char*>(&temp_value), value_size);

			float_buffer.push_back(temp_value);
		}

		for (size_t j = 0; j < size * 2; j += 2)
		{
			vector.push_back(glm::vec2(float_buffer[j], float_buffer[j + 1]));
		}

		float_buffer.clear();
	}

	template<> static void ReadVectorFromStream(std::ifstream & stream, std::vector<glm::vec3> & vector, const size_t & size)
	{
		std::vector<float> float_buffer;

		const size_t value_size = sizeof(float);

		for (size_t i = 0; i < size * 3; ++i)
		{
			float temp_value;

			stream.read(reinterpret_cast<char*>(&temp_value), value_size);

			float_buffer.push_back(temp_value);
		}

		for (size_t j = 0; j < size * 3; j += 3)
		{
			vector.push_back(glm::vec3(float_buffer[j], float_buffer[j + 1], float_buffer[j + 2]));
		}

		float_buffer.clear();
	}

	static void WriteMesh(std::ofstream & stream, const FileFormats::MeshData & mesh_input)
	{
		WriteValueToStream(stream, mesh_input.mesh_name);

		WriteValueToStream(stream, mesh_input.size_positions); 
		WriteValueToStream(stream, mesh_input.size_normals); 
		WriteValueToStream(stream, mesh_input.size_uvs);
		WriteValueToStream(stream, mesh_input.size_indices);

		WriteVectorToStream(stream, mesh_input.positions); 
		WriteVectorToStream(stream, mesh_input.normals); 
		WriteVectorToStream(stream, mesh_input.uvs);
		WriteVectorToStream(stream, mesh_input.indices);
	}

	static void ReadMesh(std::ifstream & stream, FileFormats::MeshData & mesh_output)
	{
		ReadValueFromStream(stream, mesh_output.mesh_name);

		ReadValueFromStream(stream, mesh_output.size_positions);
		ReadValueFromStream(stream, mesh_output.size_normals); 
		ReadValueFromStream(stream, mesh_output.size_uvs);
		ReadValueFromStream(stream, mesh_output.size_indices);

		ReadVectorFromStream(stream, mesh_output.positions, mesh_output.size_positions);
		ReadVectorFromStream(stream, mesh_output.normals, mesh_output.size_normals);
		ReadVectorFromStream(stream, mesh_output.uvs, mesh_output.size_uvs);
		ReadVectorFromStream(stream, mesh_output.indices, mesh_output.size_indices);
	}

	class BinaryIO
	{
	public:

	private:
		std::fstream m_file_stream;
	};
}