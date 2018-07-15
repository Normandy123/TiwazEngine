#pragma once

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <ctime>
#include <chrono>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "engine_vars.h"

namespace Tiwaz::LogSystem
{
	enum LOGTYPE : uint8_t
	{
		TIWAZ_UNDEFINED,
		TIWAZ_TEXT,
		TIWAZ_INFORMATION,
		TIWAZ_WARNING,
		TIWAZ_ERROR,
		TIWAZ_FATALERROR,

		TIWAZ_SIZE_LOG_TYPES
	};

	static const std::array<const std::string, TIWAZ_SIZE_LOG_TYPES> str_log_type =
	{
		"UNDEFINED",
		"TEXT",
		"INFORMATION",
		"WARNING",
		"ERROR",
		"FATALERROR"
	};

	class LogsBuffer;

	class Log
	{
		friend LogsBuffer;
	public:
		explicit Log(const LOGTYPE & type, const std::string & location, const std::string & text, const std::string & print_text) :
			m_type(type), m_location(location), m_text(text), m_print_text(print_text)
		{
			m_str_type = str_log_type[m_type];
		}

		~Log()
		{
			m_type = TIWAZ_UNDEFINED;
			m_str_type.clear();

			m_location.clear();
			m_text.clear();

			m_print_text.clear();
		}

		void PrintLog()
		{
			if (Global::ENGINE_DEBUG)
			{
				std::cout << m_print_text << std::endl;
			}		
		}

	private:
		LOGTYPE m_type;
		std::string m_str_type;

		std::string m_location;
		std::string m_text;

		std::string m_print_text;
	};

	class LogsBuffer
	{
	public:
		LogsBuffer()
		{
			
		}

		~LogsBuffer()
		{
			if (!m_buffer.empty())
			{
				WriteLogFile();
			}

			for (Log* log : m_buffer)
			{
				delete log;
			}

			m_buffer.clear();
		}

		void AddLog(Log* message)
		{
			m_buffer.push_back(message);
		}

	private:
		std::vector<Log*> m_buffer;

		void WriteLogFile()
		{
			std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();

			tm* time_block = new tm;
			std::time_t tt = std::chrono::system_clock::to_time_t(tp);

			localtime_s(time_block, &tt);

			std::stringstream ss_current_time; 
			ss_current_time << time_block->tm_year + 1900 << "-" << time_block->tm_mon + 1 << "-" << time_block->tm_mday << " "
				<< time_block->tm_hour << "-" << time_block->tm_min << "-" << time_block->tm_sec;

			std::filesystem::path search_path = std::filesystem::current_path();
			search_path.append("logs");
			
			if (!std::filesystem::exists(search_path))
			{
				std::filesystem::create_directory(search_path);
			}

			std::stringstream ss_file_name;
			ss_file_name << search_path.string() << "/log" << ss_current_time.str() << ".tml";
			std::string file_name = ss_file_name.str();

			std::ofstream out_log_file;
			out_log_file.open(file_name.c_str());

			out_log_file << "LOG CREATED " << ss_current_time.str() << "\n";

			for (Log* message : m_buffer)
			{
				out_log_file << message->m_print_text << "\n";
			}

			out_log_file.close();

			ss_current_time.clear();
			ss_file_name.clear();

			delete time_block;
			time_block = nullptr;
		}
	};
}

namespace Tiwaz::Global
{
	extern LogSystem::LogsBuffer* LOGS_BUFFER;
}

namespace Tiwaz
{
	extern void Log(const LogSystem::LOGTYPE & type, const std::string & location, const std::string & text);
}