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
#include "factory.h"
#include "resources_loaders.h"

//#define TIWAZ_API __declspec(dllexport)

//#include "lua_interface.h"

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

	extern int RunEngine();
	extern int ExitEngine();
}

namespace Tiwaz::Global
{
	extern Engine* ENGINE;
	extern std::thread* ENGINE_THREAD;
}