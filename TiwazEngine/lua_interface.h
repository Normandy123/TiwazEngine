#pragma once

#include <string>
#include <type_traits>

#define SOL_CHECK_ARGUMENTS 1
#include <LUA/sol.hpp>

#include "engine_object.h"
#include "component.h"
#include "graphic_component.h"
#include "message_system.h"

namespace Tiwaz::Lua
{
	template<typename TObject> const std::string TypeIDToStringName()
	{
		const std::string raw_type_name = typeid(TObject).name();
		std::string type_name; size_t find_pos, diff_pose;

		if (std::is_base_of<EngineObject, T>::value)
		{
			find_pos = raw_type_name.find("Tiwaz::");
			diff_pose = find_pos + 7;
		}

		if (std::is_base_of<Component::Component, T>::value)
		{
			find_pos = raw_type_name.find("Tiwaz::Component::");
			diff_pose = find_pos + 18;
		}

		return raw_type_name.substr(diff_pose);
	};

	class LuaInterface
	{
	public:
		LuaInterface()
		{
			lua_state.open_libraries(sol::lib::base, sol::lib::package);
		}

		~LuaInterface()
		{
			lua_state.collect_garbage();
		}

		template<typename T> void NewUserTypeConstructor(const std::string & lua_name)
		{
			lua_state.new_usertype<T>
			(
				TypeIDToStringName<T>(), sol::constructors<T()>(),
			);
		}

		int RunScript(const std::string & script_code)
		{
			try
			{
				lua_state.script(script_code);
			}
			catch (const sol::error & e)
			{ 
				const std::string warning_message = "Failed to run lua script, with sol error: " + static_cast<std::string>(e.what());
				Message(MessageSystem::TIWAZ_WARNING, "LUA_INTERFACE", warning_message);
				return -1;
			}

			return 0;
		}

		auto LuaVariable(const std::string & lua_variable_name)
		{
			return lua_state[lua_variable_name];
		}

		constexpr sol::state * AccessLuaState()
		{
			return &lua_state;
		}

	private:
		sol::state lua_state;
	};
}

namespace Tiwaz::Global
{
	extern Lua::LuaInterface * LUA_INTERFACE;
}