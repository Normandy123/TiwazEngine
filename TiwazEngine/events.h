#pragma once

#include <cstdint>

#include <string>

namespace Tiwaz::EventSystem
{
	class Event
	{
	protected:
		virtual ~Event() {};
	};

	//Basic Events
	class InitEvent : public Event
	{
	public:
	};

	class UpdateEvent : public Event
	{
	public:
		double delta_time = 0.0;
	};

	class ExitEvent : public Event
	{
	public:
	};

	//Screen Events
	class ScreenShowEvent : public Event
	{
	public:
		uint16_t width = 0;
		uint16_t height = 0;
	};

	class ScreenResizeEvent : public Event
	{
	public:
		uint16_t width = 0;
		uint16_t height = 0;
	};

	//Component Events
	class ComponentInitEvent : public InitEvent
	{
	public:
	};

	class ComponentUpdateEvent : public UpdateEvent
	{
	public:
	};

	class ComponentExitEvent : public ExitEvent
	{
	public:
	};

	//Entity Events
	class EntityInitEvent : public InitEvent
	{
	public:
	};

	class EntityUpdateEvent : public UpdateEvent
	{
	public:
	};

	class EntityExitEvent : public ExitEvent
	{
	public:
	};
}