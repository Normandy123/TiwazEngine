#include "engine.h"

int Tiwaz::Engine::Run()
{
	std::mutex run_loop_mutex;

	std::lock_guard<std::mutex> run_loop_lock(run_loop_mutex);

	Init();

	while (!Global::ENGINE_SHOULD_EXIT)
	{
		deltatime_timer.Start();

		Update();
		Render();

		Global::DELTA_TIME = deltatime_timer.DeltaTime();

		//std::cout << Global::DELTA_TIME << std::endl;
	}

	Exit();

	return 0;
}

void Tiwaz::Engine::Init()
{
	Global::ENGINE_SHOULD_EXIT = false;

	Global::MESSAGE_BUFFER = new MessageSystem::MessageBuffer;
	Global::OBJECTMANAGER = new ObjectSystem::ObjectManager;
	Global::EVENTHANDLER = new EventSystem::EventHandler;
	Global::RENDER_SCENE = new Graphic::RenderScene;
	Global::GRAPHICMANAGER = new Graphic::GraphicManager;
	//Global::LUA_INTERFACE = new Lua::LuaInterface;
	//Global::FACTORY = new Factory::Factory;

	Global::RENDER_WINDOW = new Window::Window;
	Global::RENDER_WINDOW->TiwazCreateWindow(1280, 720, "TIWAZ_ENGINE");

	EventSystem::ModelComponentInitEvent modelevent;
	//modelevent.model = Loader::LoadModel("data/models/cones2.dae");

	for (size_t i = 0; i < 100; ++i)
	{
		Component::ModelComponent* temp_obj = CreateObject<Component::ModelComponent>();
	}

	Global::EVENTHANDLER->HandleEvent(&modelevent);

	Global::EVENTHANDLER->HandleEvent(&entinit);
	Global::EVENTHANDLER->HandleEvent(&compinit);

	Global::GRAPHICMANAGER->Init();
	Global::RENDER_WINDOW->TiwazShowWindow();
}

void Tiwaz::Engine::Update()
{
	Global::EVENTHANDLER->HandleEvent(&entupdate);
	Global::EVENTHANDLER->HandleEvent(&comupdate);

	Global::RENDER_WINDOW->TiwazUpdate();
	Global::GRAPHICMANAGER->Update();
}

void Tiwaz::Engine::Render()
{
	Global::GRAPHICMANAGER->Render();
	Global::RENDER_WINDOW->TiwazSwapBuffers();
}

void Tiwaz::Engine::Exit()
{
	Global::RENDER_WINDOW->TiwazCloseWindow();

	Global::EVENTHANDLER->HandleEvent(&entexit);
	Global::EVENTHANDLER->HandleEvent(&comexit);

	//delete Global::LUA_INTERFACE;
	//Global::LUA_INTERFACE = nullptr;

	//delete Global::FACTORY;
	//Global::FACTORY = nullptr;

	Global::GRAPHICMANAGER->Exit();

	Global::RENDER_WINDOW->TiwazDestroyWindow();

	delete Global::OBJECTMANAGER;
	Global::OBJECTMANAGER = nullptr;

	delete Global::RENDER_SCENE;
	Global::RENDER_SCENE = nullptr;

	delete Global::GRAPHICMANAGER;
	Global::GRAPHICMANAGER = nullptr;

	delete Global::RENDER_WINDOW;
	Global::RENDER_WINDOW = nullptr;

	delete Global::EVENTHANDLER;
	Global::EVENTHANDLER = nullptr;

	delete Global::MESSAGE_BUFFER;
	Global::MESSAGE_BUFFER = nullptr;
}

Tiwaz::Engine* Tiwaz::Global::ENGINE;
std::thread* Tiwaz::Global::ENGINE_THREAD;

const int Tiwaz::RunEngine()
{
	if (Global::ENGINE_IS_RUNNING)
	{
		return -1;
	}

	Global::ENGINE_IS_RUNNING = true;

	Global::ENGINE = new Engine;
	Global::ENGINE_THREAD = new std::thread(&Engine::Run, Global::ENGINE);

	return 0;
}

const int Tiwaz::ExitEngine()
{
	if (!Global::ENGINE_IS_RUNNING)
	{
		return -1;
	}

	Global::ENGINE_THREAD->join();

	delete Global::ENGINE_THREAD;
	Global::ENGINE_THREAD = nullptr;

	delete Global::ENGINE;
	Global::ENGINE = nullptr;

	Global::ENGINE_IS_RUNNING = false;

	return 0;
}