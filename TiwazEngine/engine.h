#pragma once

#include <thread>
#include <future>

#include "engine_vars.h"
#include "timer.h"
#include "window.h"
#include "object_system.h"
#include "event_system.h"
#include "shader_program.h"
#include "entity.h"
#include "graphic_component.h"
#include "render_scene.h"
#include "lua_interface.h"
#include "factory.h"

#define TIWAZ_API __declspec(dllexport)

namespace Tiwaz
{
	class Engine
	{
	public:
		~Engine();
		int Run();

	private:
		void Init();
		void Update();
		void Render();
		void Exit();

		Timer::Timer* deltatime_timer = new Timer::Timer();
	};

	TIWAZ_API int RunEngine();
	TIWAZ_API int ExitEngine();
}

namespace Tiwaz::Global
{
	extern Engine* ENGINE;
	extern std::thread* ENGINE_THREAD;
}