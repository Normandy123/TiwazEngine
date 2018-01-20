#include <engine.h>

#include <boost/python.hpp>

#define BOOST_PYTHON_STATIC_LIB
BOOST_PYTHON_MODULE(TiwazPython)
{
	using namespace boost::python;
	def("RunEngine", Tiwaz::RunEngine);
	def("ExitEngine", Tiwaz::ExitEngine);
	

	class_<Tiwaz::EngineObject>("EngineObject")
		.def("Init", &Tiwaz::EngineObject::Init)
		.def("Update", &Tiwaz::EngineObject::Update)
		.def("Exit", &Tiwaz::EngineObject::Exit)
		.add_property("object_ID", &Tiwaz::EngineObject::object_ID)
		;

	def("AddObject", Tiwaz::AddObject);
}