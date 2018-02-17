#pragma once

#include <string>
#include <memory>
#include "graphic_types.h"

namespace Tiwaz::EventSystem
{
	class Event
	{
	protected:
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

	class ModelComponentInitEvent : public Event
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