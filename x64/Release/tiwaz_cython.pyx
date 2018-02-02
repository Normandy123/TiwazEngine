# distutils: language = c++
# distutils: extra_compile_args = [/std:c++latest, /Ox]
# distutils: include_dirs = [C:\Users\Oli\Documents\Visual Studio 2017\Projects\TiwazEngineDev\TiwazEngine, C:\Users\Oli\Documents\Visual Studio 2017\Projects\TiwazEngineDev\TiwazEngine\Include]
# distutils: library_dirs = [C:\Users\Oli\Documents\Visual Studio 2017\Projects\TiwazEngineDev\TiwazEngine\Lib, C:\Users\Oli\Documents\Visual Studio 2017\Projects\TiwazEngineDev\x64\Release]
# distutils: libraries = [TiwazEngine, glew32, opengl32, gdi32, user32]

from libc.stdint cimport uint64_t
from libcpp.vector cimport vector

cdef extern from "engine.h" namespace "Tiwaz":
	int RunEngine()
	int ExitEngine()
	
def run_engine():
	cdef int result = RunEngine()

	global global_OBJECTMANAGER
	
	global_OBJECTMANAGER  = PyObjectManager()
	return result

def exit_engine():
	global global_OBJECTMANAGER

	del global_OBJECTMANAGER

	return ExitEngine()

cdef extern from "object_system.h" namespace "Tiwaz::ObjectSystem":
	cdef cppclass ObjectManager:
		ObjectManager() except +
		const uint64_t AddObject(EngineObject* obj)
		void RemoveObject(const uint64_t & ID)

cdef extern from "object_system.h" namespace "Tiwaz::Global":
	cdef ObjectManager* OBJECTMANAGER
		
cdef extern from "engine_object.h" namespace "Tiwaz":
	cdef cppclass EngineObject:
		EngineObject() except +
		void Init()
		void Update()
		void Exit()
		void SetObjectID(const uint64_t & ID)
		const uint64_t object_ID()

cdef class PyObjectManager:
	cdef ObjectManager* c_object_manager
	
	py_objects = []
	
	def __cinit__(self):
		self.c_object_manager = OBJECTMANAGER
	def __dealloc__(self):
		self.c_object_manager = NULL
	def add_object(self, obj : PyEngineObject):
		self.py_objects.append(obj)	
		self.c_object_manager.AddObject(obj.c_engineobject)				
	def remove_object(self, const uint64_t & ID):
		for obj in self.py_objects:
			if obj.object_ID() == ID:
				self.py_objects.remove(obj)
				self.c_object_manager.RemoveObject(ID)
				del obj
				break
				
cdef class PyEngineObject:
	cdef EngineObject* c_engineobject
	def __cinit__(self):
		self.c_engineobject = new EngineObject()
	def __dealloc__(self):	
		del self.c_engineobject
	def init(self):
		self.c_engineobject.Init()
	def update(self):
		self.c_engineobject.Update()
	def exit(self):
		self.c_engineobject.Exit()
	def set_object_ID(self, const uint64_t & ID):
		self.c_engineobject.SetObjectID(ID)
	def object_ID(self):
		return self.c_engineobject.object_ID()