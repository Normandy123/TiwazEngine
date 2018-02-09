#pragma once

#include <type_traits>
#include <string>
#include <tuple>
#include <map>

#include "object_system.h"
#include "component.h"

namespace Tiwaz::Factory
{
	template<typename TObject> const std::string TypeIDToStringName()
	{
		const std::string raw_type_name = typeid(TObject).name();
		std::string type_name; size_t find_pos, diff_pose = 0;

		if (std::is_base_of<EngineObject, TObject>::value)
		{
			find_pos = raw_type_name.find("Tiwaz::");
			diff_pose = find_pos + 7;
		}

		if (std::is_base_of<Component::ComponentBase, TObject>::value)
		{
			find_pos = raw_type_name.find("Tiwaz::Component::");
			diff_pose = find_pos + 18;
		}

		return raw_type_name.substr(diff_pose);
	}
}