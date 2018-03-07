#pragma once

#include <string>

#define SOL_CHECK_ARGUMENTS 1
#include <LUA/sol.hpp>

#include "log_system.h"

namespace Tiwaz::Lua
{
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
				lua_name, sol::constructors<T>()
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
				Log(LogSystem::TIWAZ_WARNING, "LUA_INTERFACE", warning_message);
				return -1;
			}

			return 0;
		}

		auto LuaVariable(const std::string & lua_variable_name)
		{
			return lua_state[lua_variable_name];
		}

		constexpr sol::state* AccessLuaState()
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