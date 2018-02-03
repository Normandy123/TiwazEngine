# distutils: language = c++
# distutils: extra_compile_args = [/std:c++latest, /Ox]
# distutils: include_dirs = [C:\Users\Oli\Documents\Visual Studio 2017\Projects\TiwazEngineDev\TiwazEngine, C:\Users\Oli\Documents\Visual Studio 2017\Projects\TiwazEngineDev\TiwazEngine\Include]
# distutils: library_dirs = [C:\Users\Oli\Documents\Visual Studio 2017\Projects\TiwazEngineDev\TiwazEngine\Lib, C:\Users\Oli\Documents\Visual Studio 2017\Projects\TiwazEngineDev\x64\Release]
# distutils: libraries = [TiwazEngine, glew32, opengl32, gdi32, user32]

import gc
from libc.stdint cimport uint64_t
from libcpp.vector cimport vector
from cpython.mem cimport PyMem_Malloc, PyMem_Realloc, PyMem_Free

cdef extern from "object_system.h" namespace "Tiwaz::ObjectSystem":
	cdef cppclass ObjectManager:
		ObjectManager() except +
		const uint64_t AddObject(EngineObject* object)
		void RemoveObject(const uint64_t & ID)

cdef extern from "object_system.h" namespace "Tiwaz::Global":
	ObjectManager* OBJECTMANAGER	

cdef extern from "engine_object.h" namespace "Tiwaz":
	cdef cppclass EngineObject:
		EngineObject() except +
		void Init()
		void Update()
		void Exit()
		void SetObjectID(const uint64_t & ID)
		const uint64_t object_ID()

cdef class PyEngineObject:
	cdef EngineObject* c_engineobject
	def __cinit__(self):
		self.c_engineobject = new EngineObject()
		OBJECTMANAGER.AddObject(self.c_engineobject)
	def __dealloc__(self):
		OBJECTMANAGER.RemoveObject(self.c_engineobject.object_ID())
		del self.c_engineobject
	def init(self):
		self.c_engineobject.Init()
	def update(self):
		self.c_engineobject.Update()
	def exit(self):
		self.c_engineobject.Exit()
	def object_ID(self):
		return self.c_engineobject.object_ID()		
	
cdef extern from "engine.h" namespace "Tiwaz":
	int RunEngine()
	int ExitEngine()
	
def run_engine():
	return RunEngine()

def exit_engine():
	cdef int result = ExitEngine()
	gc.collect()
	return result