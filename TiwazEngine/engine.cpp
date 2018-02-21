#include "engine.h"

const int Tiwaz::Engine::Run()
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

	Global::MESSAGEBUFFER = new MessageSystem::MessageBuffer;
	Global::OBJECTMANAGER = new ObjectSystem::ObjectManager;
	Global::EVENTHANDLER = new EventSystem::EventHandler;
	Global::MODELLOADER = new Loader::ModelLoader;
	Global::RENDERSCENE = new Graphic::RenderScene;
	Global::GRAPHICMANAGER = new Graphic::GraphicManager;
	//Global::LUA_INTERFACE = new Lua::LuaInterface;
	//Global::FACTORY = new Factory::Factory;

	Global::RENDERWINDOW = new Window::Window;
	Global::RENDERWINDOW->TiwazCreateWindow(1280, 720, "TIWAZ_ENGINE");

	//Global::MODELLOADER->AddResource("data/models/cones2.dae");

	IO::BinaryIO binio;

	FileFormats::MeshData<3> meshdata;
	meshdata.ints[0] = 2;
	meshdata.ints[1] = 3;
	meshdata.ints[2] = 5;

	binio.Write("test.bin", meshdata);

	FileFormats::MeshData<3> meshdata2;

	binio.Read("test.bin", meshdata2);

	std::cout << meshdata2.mesh_name << std::endl;
	//std::cout << meshdata2.ints[1] << std::endl;

	for (size_t i = 0; i < 1; ++i)
	{
		Component::MeshComponent* temp_obj = CreateObject<Component::MeshComponent>();
		//temp_obj->SetMeshData(Global::MODELLOADER->AccessResource(1)->m_meshes[0]);

		/*
		std::vector<glm::vec3> temp_vec = temp_obj->Positions();

		for (size_t j = 0; j < temp_vec.size(); ++j)
		{
			std::cout << "x: " << temp_vec[j].x << "\ty: " << temp_vec[j].y << "\tz: " << temp_vec[j].z << std::endl;
		}
		*/

		/*
		for (Component::Component<Component::MeshComponent>* mesh : temp_obj->MeshComponents())
		{
			std::vector<glm::vec3> temp_vec = mesh->ptr()->Vertices();

			for (size_t j = 0; j < temp_vec.size(); ++j)
			{
				std::cout << "x: " << temp_vec[j].x << "\ty: " << temp_vec[j].y << "\tz: " << temp_vec[j].z << std::endl;
			}
		}
		*/
	}

	Global::EVENTHANDLER->HandleEvent(&entinit);
	Global::EVENTHANDLER->HandleEvent(&compinit);

	Global::GRAPHICMANAGER->Init();
	Global::RENDERWINDOW->TiwazShowWindow();
}

void Tiwaz::Engine::Update()
{
	entupdate.delta_time = Global::DELTA_TIME;
	comupdate.delta_time = Global::DELTA_TIME;

	Global::EVENTHANDLER->HandleEvent(&entupdate);
	Global::EVENTHANDLER->HandleEvent(&comupdate);

	Global::RENDERWINDOW->TiwazUpdate();
	Global::GRAPHICMANAGER->Update();
}

void Tiwaz::Engine::Render()
{
	Global::GRAPHICMANAGER->Render();
	Global::RENDERWINDOW->TiwazSwapBuffers();
}

void Tiwaz::Engine::Exit()
{
	Global::RENDERWINDOW->TiwazCloseWindow();

	Global::EVENTHANDLER->HandleEvent(&entexit);
	Global::EVENTHANDLER->HandleEvent(&comexit);

	//delete Global::LUA_INTERFACE;
	//Global::LUA_INTERFACE = nullptr;

	//delete Global::FACTORY;
	//Global::FACTORY = nullptr;

	Global::GRAPHICMANAGER->Exit();

	Global::RENDERWINDOW->TiwazDestroyWindow();

	delete Global::OBJECTMANAGER;
	Global::OBJECTMANAGER = nullptr;

	delete Global::RENDERSCENE;
	Global::RENDERSCENE = nullptr;

	delete Global::GRAPHICMANAGER;
	Global::GRAPHICMANAGER = nullptr;

	delete Global::MODELLOADER;
	Global::MODELLOADER = nullptr;

	delete Global::RENDERWINDOW;
	Global::RENDERWINDOW = nullptr;

	delete Global::EVENTHANDLER;
	Global::EVENTHANDLER = nullptr;

	delete Global::MESSAGEBUFFER;
	Global::MESSAGEBUFFER = nullptr;
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