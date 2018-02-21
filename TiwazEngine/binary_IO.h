#pragma once

#include <string>
#include <fstream>

namespace Tiwaz::IO
{
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