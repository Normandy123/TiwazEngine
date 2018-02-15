#include "message_system.h"

const std::string Tiwaz::MessageSystem::str_message_type[Tiwaz::MessageSystem::TIWAZ_SIZE_MESSAGE_TYPES] =
{
	"UNDEFINED",
	"TEXT",
	"INFORMATION",
	"WARNING",
	"ERROR",
	"FATALERROR"
};

Tiwaz::MessageSystem::MessageBuffer* Tiwaz::Global::MESSAGE_BUFFER;

void Tiwaz::Message(const MessageSystem::MessageType & type, const std::string & location, const std::string & text)
{
	MessageSystem::Message* temp_message;
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
	case MessageSystem::TIWAZ_TEXT:
		print_text += text;
		temp_message = new MessageSystem::Message(type, "", text, print_text);
		temp_message->PrintMessage();
		Global::MESSAGE_BUFFER->AddMessage(std::move(temp_message));
		break;
	case MessageSystem::TIWAZ_FATALERROR:
		print_text += MessageSystem::str_message_type[type] + ": " + location + ": " + text;
		temp_message = new MessageSystem::Message(type, location, text, print_text);
		temp_message->PrintMessage();
		Global::MESSAGE_BUFFER->AddMessage(std::move(temp_message));
		Global::ENGINE_SHOULD_EXIT = true;
		break;
	default:
		print_text += MessageSystem::str_message_type[type] + ": " + location + ": " + text;
		temp_message = new MessageSystem::Message(type, location, text, print_text);
		temp_message->PrintMessage();
		Global::MESSAGE_BUFFER->AddMessage(std::move(temp_message));
		break;
	}

	temp_message = nullptr;
}