#include "engine.h"

const int Tiwaz::Engine::Run()
{
	Init();

	while (!Global::ENGINE_SHOULD_EXIT)
	{
		Update();
		Render();

		//std::cout << Global::DELTA_TIME << std::endl;
	}

	Exit();

	return 0;
}

void Tiwaz::Engine::Init()
{
	std::unique_lock<std::mutex> engine_loop_lock(run_function_mutex);

	Global::LOGS_BUFFER = new LogSystem::LogsBuffer;
	Global::ENGINE_EVENT_HANDLER = new EventSystem::EventHandler;
	Global::RENDER_SCENE = new Graphic::RenderScene;
	Global::GRAPHIC_MANAGER = new Graphic::GraphicManager;
	Global::MAIN_RENDERER = new Graphic::MainRenderer;
	Global::OBJECTS_MANAGER = new ObjectSystem::ObjectsManager;
	//Global::FACTORY = new Factory::Factory;
	//Global::LUA_INTERFACE = new Lua::LuaInterface;

	Global::RENDER_WINDOW = new Window::RenderWindow;
	Global::RENDER_WINDOW->TiwazCreateWindow(1408, 792, "TIWAZ_ENGINE", false);

	/*
	std::vector<glm::vec3> temp_vec1 = meshdata_read->positions;

	for (size_t j = 0; j < temp_vec1.size(); ++j)
	{
		std::cout << "x: " << temp_vec1[j].x << "\ty: " << temp_vec1[j].y << "\tz: " << temp_vec1[j].z << std::endl;
	}

	std::vector<glm::vec3> temp_vec2 = meshdata_read->normals;

	for (size_t j = 0; j < temp_vec2.size(); ++j)
	{
		std::cout << "x: " << temp_vec2[j].x << "\ty: " << temp_vec2[j].y << "\tz: " << temp_vec2[j].z << std::endl;
	}

	std::vector<glm::vec2> temp_vec3 = meshdata_read->uvs;

	for (size_t j = 0; j < temp_vec3.size(); ++j)
	{
		std::cout << "x: " << temp_vec3[j].x << "\ty: " << temp_vec3[j].y << std::endl;
	}

	std::vector<unsigned int> temp_vec4 = meshdata_read->indices;

	for (size_t j = 0; j < temp_vec4.size(); ++j)
	{
		std::cout << temp_vec4[j] << std::endl;
	}
	*/

	Resources::ResourcesManager test2;

	test2.ReadResource<Resources::MESH>("cone");
	test2.ReadResource<Resources::MESH>("cone.001");
	test2.ReadResource<Resources::MESH>("cone.002");

	Global::ENGINE_EVENT_HANDLER->HandleEvent(&entinit);
	Global::ENGINE_EVENT_HANDLER->HandleEvent(&compinit);

	Global::GRAPHIC_MANAGER->Init();
	Global::RENDER_WINDOW->TiwazShowWindow();
}

void Tiwaz::Engine::Update()
{
	std::unique_lock<std::mutex> engine_loop_lock(run_function_mutex);

	deltatime_timer.Start();

	entupdate.delta_time = Global::DELTA_TIME;
	comupdate.delta_time = Global::DELTA_TIME;

	Global::ENGINE_EVENT_HANDLER->HandleEvent(&entupdate);
	Global::ENGINE_EVENT_HANDLER->HandleEvent(&comupdate);

	Global::RENDER_WINDOW->TiwazUpdate();
	Global::GRAPHIC_MANAGER->Update();
}

void Tiwaz::Engine::Render()
{
	std::unique_lock<std::mutex> engine_loop_lock(run_function_mutex);

	Global::GRAPHIC_MANAGER->Render();
	Global::RENDER_WINDOW->TiwazSwapBuffers();

	Global::DELTA_TIME = deltatime_timer.DeltaTime();
}

void Tiwaz::Engine::Exit()
{
	std::unique_lock<std::mutex> engine_loop_lock(run_function_mutex);

	Global::RENDER_WINDOW->TiwazCloseWindow();

	Global::ENGINE_EVENT_HANDLER->HandleEvent(&entexit);
	Global::ENGINE_EVENT_HANDLER->HandleEvent(&comexit);

	Global::GRAPHIC_MANAGER->Exit();
	Global::RENDER_WINDOW->TiwazDestroyWindow();

	//delete Global::LUA_INTERFACE;
	//Global::LUA_INTERFACE = nullptr;

	//delete Global::FACTORY;
	//Global::FACTORY = nullptr;

	delete Global::OBJECTS_MANAGER;
	Global::OBJECTS_MANAGER = nullptr;

	delete Global::MAIN_RENDERER;
	Global::MAIN_RENDERER = nullptr;

	delete Global::RENDER_SCENE;
	Global::RENDER_SCENE = nullptr;

	delete Global::GRAPHIC_MANAGER;
	Global::GRAPHIC_MANAGER = nullptr;

	delete Global::RENDER_WINDOW;
	Global::RENDER_WINDOW = nullptr;

	delete Global::ENGINE_EVENT_HANDLER;
	Global::ENGINE_EVENT_HANDLER = nullptr;

	delete Global::LOGS_BUFFER;
	Global::LOGS_BUFFER = nullptr;
}

Tiwaz::Engine* Tiwaz::Global::ENGINE;
std::thread* Tiwaz::Global::ENGINE_THREAD;

const int Tiwaz::RunEngine(bool debug, bool editor)
{
	if (Global::ENGINE_IS_RUNNING)
	{
		return -1;
	}

	Global::ENGINE_DEBUG = debug;
	Global::ENGINE_EDITOR = editor;
	Global::ENGINE_SHOULD_EXIT = false;
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