#include "log_system.h"

Tiwaz::LogSystem::LogsBuffer* Tiwaz::Global::LOGS_BUFFER;

void Tiwaz::Log(const LogSystem::LOGTYPE & type, const std::string & location, const std::string & text)
{
	LogSystem::Log* temp_log;
	std::string print_text;

	std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();

	tm* time_block = new tm;
	std::time_t tt = std::chrono::system_clock::to_time_t(tp);

	localtime_s(time_block, &tt);

	std::stringstream ss_current_time;
	ss_current_time << time_block->tm_year + 1900 << "-" << time_block->tm_mon + 1 << "-" << time_block->tm_mday << " "
		<< time_block->tm_hour << "-" << time_block->tm_min << "-" << time_block->tm_sec;

	print_text = ss_current_time.str() + " TIWAZENGINE: ";

	delete time_block;
	time_block = nullptr;

	switch (type)
	{
	case LogSystem::TIWAZ_TEXT:
		print_text += text;
		temp_log = new LogSystem::Log(type, "", text, print_text);
		temp_log->PrintLog();
		Global::LOGS_BUFFER->AddLog(std::move(temp_log));
		break;
	case LogSystem::TIWAZ_FATALERROR:
		print_text += LogSystem::STRINGLOGTYPES[type] + ": " + location + ": " + text;
		temp_log = new LogSystem::Log(type, location, text, print_text);
		temp_log->PrintLog();
		Global::LOGS_BUFFER->AddLog(std::move(temp_log));
		Global::ENGINE_SHOULD_EXIT = true;
		break;
	default:
		print_text += LogSystem::STRINGLOGTYPES[type] + ": " + location + ": " + text;
		temp_log = new LogSystem::Log(type, location, text, print_text);
		temp_log->PrintLog();
		Global::LOGS_BUFFER->AddLog(std::move(temp_log));
		break;
	}

	temp_log = nullptr;
}