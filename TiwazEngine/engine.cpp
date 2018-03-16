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

	Global::LOGBUFFER = new LogSystem::LogsBuffer;
	Global::OBJECTMANAGER = new ObjectSystem::ObjectManager;
	Global::ENGINEEVENTHANDLER = new EventSystem::EventHandler;
	Global::RENDERSCENE = new Graphic::RenderScene;
	Global::GRAPHICMANAGER = new Graphic::GraphicManager;
	//Global::LUA_INTERFACE = new Lua::LuaInterface;
	//Global::FACTORY = new Factory::Factory;

	Global::RENDERWINDOW = new Window::RenderWindow;
	Global::RENDERWINDOW->TiwazCreateWindow(1408, 792, "TIWAZ_ENGINE", false);

	ResourcesIO::ResourcesManager<ResourcesFileFormats::ModelData> rsma(&ResourcesIO::LoadModel);
	rsma.AddResource("data/models/cones2.dae");

	ResourcesFileFormats::ModelData* test1 = rsma.AccessResource(1);

	BinaryIO::BinaryIOManager bm;

	bm.Write("test.bin", &BinaryIO::WriteMesh, test1->meshes[0]);

	BinaryFileFormats::MeshData* meshdata_read = new BinaryFileFormats::MeshData();
	bm.Read("test.bin", &BinaryIO::ReadMesh, meshdata_read);

	std::cout << meshdata_read->mesh_name << std::endl;

	std::cout << std::endl;

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

	delete meshdata_read;

	for (size_t i = 0; i < 1; ++i)
	{
		Component::MeshComponent* temp_obj = CreateObject<Component::MeshComponent>();
	}

	Global::ENGINEEVENTHANDLER->HandleEvent(&entinit);
	Global::ENGINEEVENTHANDLER->HandleEvent(&compinit);

	Global::GRAPHICMANAGER->Init();
	Global::RENDERWINDOW->TiwazShowWindow();
}

void Tiwaz::Engine::Update()
{
	entupdate.delta_time = Global::DELTA_TIME;
	comupdate.delta_time = Global::DELTA_TIME;

	Global::ENGINEEVENTHANDLER->HandleEvent(&entupdate);
	Global::ENGINEEVENTHANDLER->HandleEvent(&comupdate);

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

	Global::ENGINEEVENTHANDLER->HandleEvent(&entexit);
	Global::ENGINEEVENTHANDLER->HandleEvent(&comexit);

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

	delete Global::RENDERWINDOW;
	Global::RENDERWINDOW = nullptr;

	delete Global::ENGINEEVENTHANDLER;
	Global::ENGINEEVENTHANDLER = nullptr;

	delete Global::LOGBUFFER;
	Global::LOGBUFFER = nullptr;
}

Tiwaz::Engine* Tiwaz::Global::ENGINE;
std::thread* Tiwaz::Global::ENGINE_THREAD;

const int Tiwaz::RunEngine(bool debug, bool editor)
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