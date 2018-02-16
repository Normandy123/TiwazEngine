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
		std::shared_ptr<Graphic::Model> model;
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