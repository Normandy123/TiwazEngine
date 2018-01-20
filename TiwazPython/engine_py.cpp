#include <engine.h>

#include <boost/python.hpp>

#define BOOST_PYTHON_STATIC_LIB
BOOST_PYTHON_MODULE(TiwazPython)
{
	using namespace boost::python;
	def("RunEngine", Tiwaz::RunEngine);
	def("ExitEngine", Tiwaz::ExitEngine);
}