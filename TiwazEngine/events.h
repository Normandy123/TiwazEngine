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
	};

	class ComponentUpdateEvent : public Event
	{
	public:
	};

	class ComponentExitEvent : public Event
	{
	public:
	};

	class EntityInitEvent : public Event
	{
	public:
	};

	class EntityUpdateEvent : public Event
	{
	public:
	};

	class EntityExitEvent : public Event
	{
	public:
	};
}