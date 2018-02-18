#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>

#include "engine_vars.h"

namespace Tiwaz::MessageSystem
{
	enum MessageType : uint8_t
	{
		TIWAZ_UNDEFINED,
		TIWAZ_TEXT,
		TIWAZ_INFORMATION,
		TIWAZ_WARNING,
		TIWAZ_ERROR,
		TIWAZ_FATALERROR,

		TIWAZ_SIZE_MESSAGE_TYPES
	};

	extern const std::string str_message_type[TIWAZ_SIZE_MESSAGE_TYPES];

	class MessageBuffer;

	class Message
	{
		friend MessageBuffer;
	public:
		Message(const MessageType & type, const std::string & location, const std::string & text, const std::string & print_text) :
			m_type(type), m_location(location), m_text(text), m_print_text(print_text)
		{
			m_str_type = str_message_type[m_type];
		}

		~Message()
		{
			m_type = TIWAZ_UNDEFINED;
			m_str_type.clear();

			m_location.clear();
			m_text.clear();

			m_print_text.clear();
		}

		void PrintMessage()
		{
			std::cout << m_print_text << std::endl;
		}

	private:
		MessageType m_type;
		std::string m_str_type;

		std::string m_location;
		std::string m_text;

		std::string m_print_text;
	};

	class MessageBuffer
	{
	public:
		MessageBuffer()
		{
			
		}

		~MessageBuffer()
		{
			if (!m_buffer.empty())
			{
				WriteMessageLogFile();
			}

			for (Message* message : m_buffer)
			{
				delete message;
				message = nullptr;
			}

			m_buffer.clear();
		}

		void AddMessage(Message* message)
		{
			m_buffer.push_back(message);
		}

	private:
		std::vector<Message*> m_buffer;

		void WriteMessageLogFile()
		{
			std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();

			tm* time_block = new tm;
			std::time_t tt = std::chrono::system_clock::to_time_t(tp);

			localtime_s(time_block, &tt);

			std::stringstream ss_current_time; 
			ss_current_time << time_block->tm_year + 1900 << "-" << time_block->tm_mon + 1 << "-" << time_block->tm_mday << " "
				<< time_block->tm_hour << "-" << time_block->tm_min << "-" << time_block->tm_sec;

			std::stringstream ss_file_name; 
			ss_file_name << "logs/log" << ss_current_time.str() << ".tml";
			std::string file_name = ss_file_name.str();

			std::ofstream out_log_file;
			out_log_file.open(file_name.c_str());

			out_log_file << "LOG CREATED " << ss_current_time.str() << "\n";

			for (Message* message : m_buffer)
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
	extern MessageSystem::MessageBuffer* MESSAGEBUFFER;
}

namespace Tiwaz
{
	extern void Message(const MessageSystem::MessageType & type, const std::string & location, const std::string & text);
}