#pragma once

#include <string>
#include <vector>
#include <fstream>

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
		const size_t value_size = sizeof(T);
		
		std::vector<char*> temp_char_vector;

		for (T value : vector)
		{
			temp_char_vector.push_back(reinterpret_cast<char*>(value));
		}

		for (char* value : temp_char_vector)
		{
			stream.write(value, value_size);
		}

		temp_char_vector.clear();
	}

	template<> static void WriteVectorToStream(std::ofstream & stream, std::vector<glm::vec2> vector)
	{
		const size_t value_size = sizeof(float);

		std::vector<char*> temp_char_vector;

		for (glm::vec2 value : vector)
		{
			char char_float_x[4];
			memcpy(char_float_x, &value.x, 4);
			char char_float_y[4];
			memcpy(char_float_y, &value.y, 4);

			temp_char_vector.push_back(char_float_x);
			temp_char_vector.push_back(char_float_y);
		}

		for (char* value : temp_char_vector)
		{
			stream.write(value, value_size);
		}

		temp_char_vector.clear();
	}

	template<> static void WriteVectorToStream(std::ofstream & stream, std::vector<glm::vec3> vector)
	{
		const size_t value_size = sizeof(float);

		std::vector<char*> temp_char_vector;

		for (glm::vec3 value : vector)
		{
			char char_float_x[value_size];
			char char_float_y[value_size];
			char char_float_z[value_size];

			CopyToCharPointer(char_float_x, value.x);
			CopyToCharPointer(char_float_y, value.y);
			CopyToCharPointer(char_float_z, value.z);

			temp_char_vector.push_back(char_float_x);
			temp_char_vector.push_back(char_float_y);
			temp_char_vector.push_back(char_float_z);
		}

		for (char* value : temp_char_vector)
		{
			stream.write(value, value_size);
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

		std::vector<char*> temp_char_vector;

		for (size_t i = 0; i < size; ++i)
		{
			char temp_char[value_size];
			stream.read(temp_char, value_size);

			temp_char_vector.push_back(temp_char);
		}

		for(char* value : temp_char_vector)
		{
			vector.push_back(reinterpret_cast<T>(value));
		}

		temp_char_vector.clear();
	}

	template<> static void ReadVectorFromStream(std::ifstream & stream, std::vector<glm::vec3> & vector, const size_t & size)
	{
		const size_t value_size = sizeof(float);

		std::vector<float> temp_float_vector;

		//TODO: reading glm::vec3 vector

		/*
		for (size_t i = 0; i < size * 3; ++i)
		{
			char temp_char[value_size];
			stream.read(temp_char, value_size);

			float x = 0;
			CopyToTypeRef(temp_char, x);

			temp_float_vector.push_back(x);
		}

		for (size_t i = 0; i <= temp_float_vector.size(); i += 3)
		{
			float x = 0, y = 0, z = 0;
			x = temp_float_vector[i];
			y = temp_float_vector[i + 1];
			z = temp_float_vector[i + 2];
			vector.push_back(glm::vec3(x, y, z));

			if ((i + 3) > temp_float_vector.size())
				break;
		}
		*/

		temp_float_vector.clear();
	}

	static void WriteMesh(std::ofstream & stream, const FileFormats::MeshData & mesh_input)
	{
		WriteValueToStream(stream, mesh_input.mesh_name);

		WriteValueToStream(stream, mesh_input.size_positions); 
		WriteValueToStream(stream, mesh_input.size_normals); 
		WriteValueToStream(stream, mesh_input.size_uvs);

		WriteVectorToStream(stream, mesh_input.positions); 
		WriteVectorToStream(stream, mesh_input.normals); 
		WriteVectorToStream(stream, mesh_input.uvs);
	}

	static void ReadMesh(std::ifstream & stream, FileFormats::MeshData & mesh_output)
	{
		ReadValueFromStream(stream, mesh_output.mesh_name);
		ReadValueFromStream(stream, mesh_output.size_positions); ReadValueFromStream(stream, mesh_output.size_normals); ReadValueFromStream(stream, mesh_output.size_uvs);
		ReadVectorFromStream(stream, mesh_output.positions, mesh_output.size_positions);
	}

	class BinaryIO
	{
	public:

	private:
		std::fstream m_file_stream;
	};
}