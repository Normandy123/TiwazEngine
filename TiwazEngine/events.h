#pragma once

#include <string>

namespace Tiwaz::EventSystem
{
	class Event
	{
	public:
		virtual ~Event() {};
	};

	class ComponentInitEvent : public Event
	{
	public:
		std::string text;
	};
}