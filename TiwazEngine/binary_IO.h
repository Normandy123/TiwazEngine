#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "file_types.h"

namespace Tiwaz::IO
{
	template<typename T, size_t TSize = sizeof(T)> static void CopyToCharPointer(char* char_float, T value)
	{
		memcpy(char_float, &value, TSize);
	}

	template<typename T> static void WriteValueToStream(std::ofstream & stream, T data)
	{
		stream.write(reinterpret_cast<char*>(&data), sizeof(T));
	}

	template<typename T> static void WriteVectorToStream(std::ofstream & stream, std::vector<T> vector)
	{	
		if (!vector.empty())
		{
			const size_t value_size = sizeof(T);

			std::vector<char*> temp_char_vector;

			char* char_value;

			for (T input_vector_value : vector)
			{
				char_value = new char[value_size];

				CopyToCharPointer(char_value, input_vector_value);

				temp_char_vector.push_back(char_value);

				char_value = nullptr;
			}

			for (char* char_vector_value : temp_char_vector)
			{
				stream.write(char_vector_value, value_size);
			}

			for (char* value : temp_char_vector)
			{
				delete[] value;
				value = nullptr;
			}

			temp_char_vector.clear();
		}
	}

	template<> static void WriteVectorToStream(std::ofstream & stream, std::vector<glm::vec2> vector)
	{
		const size_t value_size = sizeof(float);

		std::vector<char*> temp_char_vector;

		for (glm::vec2 input_vector_value : vector)
		{
			char char_float_x[value_size];
			char char_float_y[value_size];

			CopyToCharPointer(char_float_x, input_vector_value.x);
			CopyToCharPointer(char_float_y, input_vector_value.y);

			temp_char_vector.push_back(char_float_x);
			temp_char_vector.push_back(char_float_y);
		}

		for (char* char_vector_value : temp_char_vector)
		{
			stream.write(char_vector_value, value_size);
		}

		temp_char_vector.clear();
	}

	template<> static void WriteVectorToStream(std::ofstream & stream, std::vector<glm::vec3> vector)
	{
		const size_t value_size = sizeof(float);

		std::vector<char*> temp_char_vector;

		for (glm::vec3 input_vector_value : vector)
		{
			char char_float_x[value_size];
			char char_float_y[value_size];
			char char_float_z[value_size];

			CopyToCharPointer(char_float_x, input_vector_value.x);
			CopyToCharPointer(char_float_y, input_vector_value.y);
			CopyToCharPointer(char_float_z, input_vector_value.z);

			temp_char_vector.push_back(char_float_x);
			temp_char_vector.push_back(char_float_y);
			temp_char_vector.push_back(char_float_z);
		}

		for (char* char_vector_value : temp_char_vector)
		{
			stream.write(char_vector_value, value_size);
		}

		temp_char_vector.clear();
	}

	template<typename T, size_t TSize = sizeof(T)> static void CopyToTypeRef(char* char_float, T & value)
	{
		memcpy(&value, char_float, TSize);
	}

	template<typename T> static void ReadValueFromStream(std::ifstream & stream, T & data)
	{
		stream.read(reinterpret_cast<char*>(&data), sizeof(T));
	}

	template<typename T> static void ReadVectorFromStream(std::ifstream & stream, std::vector<T> & vector, const size_t & size)
	{
		const size_t value_size = sizeof(T);
	}

	template<> static void ReadVectorFromStream(std::ifstream & stream, std::vector<glm::vec2> & vector, const size_t & size)
	{
		const size_t value_size = sizeof(float);
	}

	template<> static void ReadVectorFromStream(std::ifstream & stream, std::vector<glm::vec3> & vector, const size_t & size)
	{
		const size_t value_size = sizeof(float);
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