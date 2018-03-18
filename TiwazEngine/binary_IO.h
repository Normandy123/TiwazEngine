#pragma once

#include <string>
#include <vector>

#include <fstream>

#include <type_traits>

#include "file_formats.h"

namespace Tiwaz::BinaryIO
{
	constexpr size_t BYTE_SIZE_SIZE_T = sizeof(size_t);
	constexpr size_t BYTE_SIZE_FLOAT = sizeof(float);

	template<typename T> static void WriteValueToStream(std::ofstream & stream, T data)
	{
		stream.write(reinterpret_cast<const char*>(&data), sizeof(T));
	}

	template<> static void WriteValueToStream(std::ofstream & stream, std::string data)
	{
		const size_t string_size = data.size();

		stream.write(reinterpret_cast<const char*>(&string_size), BYTE_SIZE_SIZE_T);
		stream.write(data.c_str(), string_size);
	}

	template<typename T> static void WriteVectorToStream(std::ofstream & stream, std::vector<T> vector)
	{	
		const size_t value_size = sizeof(T);
		const size_t data_size = vector.size() * value_size;

		stream.write(reinterpret_cast<const char*>(&data_size), BYTE_SIZE_SIZE_T);

		for (const T vector_value : vector)
		{
			stream.write(reinterpret_cast<const char*>(&vector_value), value_size);
		}
	}

	template<> static void WriteVectorToStream(std::ofstream & stream, std::vector<glm::vec2> vector)
	{
		const size_t data_size = vector.size() * BYTE_SIZE_FLOAT * 2;

		stream.write(reinterpret_cast<const char*>(&data_size), BYTE_SIZE_SIZE_T);

		std::vector<float> float_buffer;

		for (const glm::vec2 vector_value : vector)
		{
			float_buffer.push_back(vector_value.x);
			float_buffer.push_back(vector_value.y);
		}

		for (const float vector_value : float_buffer)
		{
			stream.write(reinterpret_cast<const char*>(&vector_value), BYTE_SIZE_FLOAT);
		}

		float_buffer.clear();
	}

	template<> static void WriteVectorToStream(std::ofstream & stream, std::vector<glm::vec3> vector)
	{
		const size_t data_size = vector.size() * BYTE_SIZE_FLOAT * 3;

		stream.write(reinterpret_cast<const char*>(&data_size), BYTE_SIZE_SIZE_T);

		std::vector<float> float_buffer;

		for (const glm::vec3 vector_value : vector)
		{
			float_buffer.push_back(vector_value.x);
			float_buffer.push_back(vector_value.y);
			float_buffer.push_back(vector_value.z);
		}

		for (const float vector_value : float_buffer)
		{
			stream.write(reinterpret_cast<const char*>(&vector_value), BYTE_SIZE_FLOAT);
		}

		float_buffer.clear();
	}

	template<typename T> static void ReadValueFromStream(std::ifstream & stream, T & data)
	{
		stream.read(reinterpret_cast<char*>(&data), sizeof(T));
	}

	template<> static void ReadValueFromStream(std::ifstream & stream, std::string & data)
	{
		size_t string_size = 0;
		stream.read(reinterpret_cast<char*>(&string_size), BYTE_SIZE_SIZE_T);

		char* raw_string = new char[string_size];

		stream.read(raw_string, string_size);
		data = std::string(raw_string, string_size);

		delete[] raw_string;
	}

	template<typename T> static void ReadVectorFromStream(std::ifstream & stream, std::vector<T> & vector)
	{
		const size_t value_size = sizeof(T);

		size_t data_size = 0;
		stream.read(reinterpret_cast<char*>(&data_size), BYTE_SIZE_SIZE_T);
		const size_t vector_size = data_size / value_size;

		for (size_t i = 0; i < vector_size; ++i)
		{
			T temp_value;

			stream.read(reinterpret_cast<char*>(&temp_value), value_size);

			vector.push_back(temp_value);
		}
	}

	template<> static void ReadVectorFromStream(std::ifstream & stream, std::vector<glm::vec2> & vector)
	{
		std::vector<float> float_buffer;

		size_t data_size = 0;
		stream.read(reinterpret_cast<char*>(&data_size), BYTE_SIZE_SIZE_T);
		const size_t vector_size = data_size / BYTE_SIZE_FLOAT;

		for (size_t i = 0; i < vector_size; ++i)
		{
			float temp_value = 0.0f;

			stream.read(reinterpret_cast<char*>(&temp_value), BYTE_SIZE_FLOAT);

			float_buffer.push_back(temp_value);
		}

		for (size_t j = 0; j < vector_size; j += 2)
		{
			vector.push_back(glm::vec2(float_buffer[j], float_buffer[j + 1]));
		}

		float_buffer.clear();
	}

	template<> static void ReadVectorFromStream(std::ifstream & stream, std::vector<glm::vec3> & vector)
	{
		std::vector<float> float_buffer;

		size_t data_size = 0;
		stream.read(reinterpret_cast<char*>(&data_size), BYTE_SIZE_SIZE_T);
		const size_t size_vector = data_size / BYTE_SIZE_FLOAT;

		for (size_t i = 0; i < size_vector; ++i)
		{
			float temp_value = 0.0f;

			stream.read(reinterpret_cast<char*>(&temp_value), BYTE_SIZE_FLOAT);

			float_buffer.push_back(temp_value);
		}

		for (size_t j = 0; j < size_vector; j += 3)
		{
			vector.push_back(glm::vec3(float_buffer[j], float_buffer[j + 1], float_buffer[j + 2]));
		}

		float_buffer.clear();
	}

	static void WriteMesh(const std::string & file_path, FileFormats::MeshData* mesh_input)
	{
		if (file_path != "" && file_path != "UNDEFINED")
		{
			std::ofstream stream;

			stream.open(file_path, std::ios::binary);

			if (stream.is_open() && !stream.fail())
			{
				WriteValueToStream(stream, mesh_input->mesh_name);

				WriteVectorToStream(stream, mesh_input->positions);
				WriteVectorToStream(stream, mesh_input->normals);
				WriteVectorToStream(stream, mesh_input->uvs);
				WriteVectorToStream(stream, mesh_input->indices);
			}

			stream.close();
		}
	}

	static void ReadMesh(const std::string & file_path, FileFormats::MeshData* mesh_output)
	{
		if (file_path != "" && file_path != "UNDEFINED")
		{
			std::ifstream stream;

			stream.open(file_path, std::ios::binary);

			if (stream.is_open() && !stream.fail())
			{
				ReadValueFromStream(stream, mesh_output->mesh_name);

				ReadVectorFromStream(stream, mesh_output->positions);
				ReadVectorFromStream(stream, mesh_output->normals);
				ReadVectorFromStream(stream, mesh_output->uvs);
				ReadVectorFromStream(stream, mesh_output->indices);

				stream.close();
			}
		}
	}
}