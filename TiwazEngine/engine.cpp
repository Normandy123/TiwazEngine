#include "engine.h"

Tiwaz::Engine::~Engine()
{
	delete deltatime_timer;
	deltatime_timer = nullptr;
}

int Tiwaz::Engine::Run()
{
	std::mutex run_loop_mutex;

	std::lock_guard<std::mutex> run_loop_lock(run_loop_mutex);

	Init();

	while (!Global::SHOULD_EXIT)
	{
		deltatime_timer->Start();

		Update();
		Render();

		Global::DELTA_TIME = deltatime_timer->DeltaTime();

		//std::cout << Global::DELTA_TIME << std::endl;
	}

	Exit();

	return 0;
}

void Tiwaz::Engine::Init()
{
	Global::SHOULD_EXIT = false;

	Global::MESSAGE_BUFFER = new MessageSystem::MessageBuffer;
	Global::OBJECTMANAGER = new ObjectSystem::ObjectManager;
	Global::EVENTMANAGER = new EventSystem::EventsManager;
	Global::RENDER_SCENE = new Graphic::RenderScene;
	//Global::LUA_INTERFACE = new Lua::LuaInterface;
	//Global::FACTORY = new Factory::Factory;

	Global::RENDER_WINDOW = new Window::Window;

	Global::RENDER_WINDOW->TiwazCreateWindow(1280, 720, "TIWAZ_ENGINE");

	glClearColor(0.2f, 0.5f, 0.7f, 1.0f);

	Global::RENDER_WINDOW->TiwazShowWindow();

	Component::MeshComponent* p_mesh = new Component::MeshComponent();
	auto t = p_mesh->Vertices();
	for (size_t i = 0; i < t.size(); i++)
	{
		std::cout << "x: " << t[i][0] << " y: " << t[i][1] << " z: " << t[i][2] << std::endl;
	}

	auto t2 = Global::RENDER_SCENE->Components();
	for (size_t i = 0; i < t2->size(); i++)
	{
		std::cout << (*t2)[i] << std::endl;
	}

	std::cout << p_mesh << std::endl;

	Global::EVENTMANAGER->LaunchEvent("ENTITY_INIT");
	Global::EVENTMANAGER->LaunchEvent("COMPONENT_INIT");
}

void Tiwaz::Engine::Update()
{
	Global::RENDER_WINDOW->TiwazUpdate();

	Global::EVENTMANAGER->LaunchEvent("ENTITY_UPDATE");
	Global::EVENTMANAGER->LaunchEvent("COMPONENT_UPDATE");
}

void Tiwaz::Engine::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5, 0.0, 0.0);
	glVertex3f(0.0, 0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glEnd();

	Global::RENDER_WINDOW->TiwazSwapBuffers();
}

void Tiwaz::Engine::Exit()
{
	Global::EVENTMANAGER->LaunchEvent("ENTITY_EXIT");
	Global::EVENTMANAGER->LaunchEvent("COMPONENT_EXIT");

	//delete Global::LUA_INTERFACE;
	//Global::LUA_INTERFACE = nullptr;

	//delete Global::FACTORY;
	//Global::FACTORY = nullptr;

	Global::RENDER_WINDOW->TiwazDestroyWindow();

	delete Global::RENDER_SCENE;
	Global::RENDER_SCENE = nullptr;

	delete Global::OBJECTMANAGER;
	Global::OBJECTMANAGER = nullptr;

	delete Global::EVENTMANAGER;
	Global::EVENTMANAGER = nullptr;

	delete Global::RENDER_WINDOW;
	Global::RENDER_WINDOW = nullptr;

	delete Global::MESSAGE_BUFFER;
	Global::MESSAGE_BUFFER = nullptr;
}

Tiwaz::Engine* Tiwaz::Global::ENGINE;
std::thread* Tiwaz::Global::ENGINE_THREAD;

int Tiwaz::RunEngine()
{
	Global::ENGINE = new Engine;
	Global::ENGINE_THREAD = new std::thread(&Engine::Run, Global::ENGINE);

	return 0;
}

int Tiwaz::ExitEngine()
{
	Global::ENGINE_THREAD->join();

	delete Global::ENGINE_THREAD;
	Global::ENGINE_THREAD = nullptr;

	delete Global::ENGINE;
	Global::ENGINE = nullptr;

	return 0;
}
