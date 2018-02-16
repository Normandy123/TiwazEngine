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
		int Run();

	private:
		void Init();
		void Update();
		void Render();
		void Exit();

		Timer::Timer deltatime_timer;

		EventSystem::EntityInitEvent entinit;
		EventSystem::ComponentInitEvent compinit;

		EventSystem::EntityUpdateEvent entupdate;
		EventSystem::ComponentUpdateEvent comupdate;

		EventSystem::EntityExitEvent entexit;
		EventSystem::ComponentExitEvent comexit;
	};

	extern const int RunEngine();
	extern const int ExitEngine();
}

namespace Tiwaz::Global
{
	extern Engine* ENGINE;
	extern std::thread* ENGINE_THREAD;
}