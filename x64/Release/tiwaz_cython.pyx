# distutils: language = c++
# distutils: extra_compile_args = [/std:c++latest, /Ox]
# distutils: include_dirs = [C:\Users\Oli\Documents\Visual Studio 2017\Projects\TiwazEngineDev\TiwazEngine, C:\Users\Oli\Documents\Visual Studio 2017\Projects\TiwazEngineDev\TiwazEngine\Include]
# distutils: library_dirs = [C:\Users\Oli\Documents\Visual Studio 2017\Projects\TiwazEngineDev\TiwazEngine\Lib, C:\Users\Oli\Documents\Visual Studio 2017\Projects\TiwazEngineDev\x64\Release]
# distutils: libraries = [TiwazEngine, glew32, opengl32, gdi32, user32]

import gc
from libc.stdint cimport uint64_t
from libcpp.vector cimport vector

c_garbage = []

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
		c_garbage.append(self)
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

cdef extern from "component.h" namespace "Tiwaz::Component":
	cdef cppclass Component:
		Component() except +

cdef extern from "graphic_component.h" namespace "Tiwaz::Component":
	cdef cppclass GraphicComponent:
		pass

cdef extern from "graphic_component.h" namespace "Tiwaz::Component":
	ctypedef vector[float] vec
	cdef cppclass MeshComponent:
		MeshComponent() except +
		const vector[vec] Vertices()
		const vector[vec] Normals()
		const vector[vec] UVs()

cpdef c_vector_to_py_list(vector[vec] in_vec):
	result = []

	cdef size_t size = in_vec.size()
	cdef size_t size_2 = in_vec[0].size()
	cdef size_t i = 0
	cdef size_t j = 0
	for i in range(size):
		value = []
		j = 0
		for j in range(size_2):
			value.append(<float>in_vec[i][j])
			
		result.append(value)
		
	return result
		
cdef class PyComponent(PyEngineObject):
	cdef Component* c_component
	def __cinit__(self):	
		self.c_component = new Component()
	def __dealloc__(self):
		del self.c_component
		
cdef class PyGraphicComponent(PyComponent):
	pass

cdef class PyMeshComponent(PyGraphicComponent):
	cdef MeshComponent* c_mesh_component
	def __cinit__(self):
		self.c_mesh_component = new MeshComponent()
	def __dealloc__(self):
		del self.c_mesh_component
	def vertices(self):
		return self.c_mesh_component.Vertices()
	def normals(self):
		return self.c_mesh_component.Normals()
	def uvs(self):
		return self.c_mesh_component.UVs()

cdef extern from "engine.h" namespace "Tiwaz":
	int RunEngine()
	int ExitEngine()
	
def run_engine():
	return RunEngine()

def exit_engine():
	for obj in c_garbage:
		print(obj)
	for obj in c_garbage:
		del obj
	cdef int result = ExitEngine()
	gc.collect()
	return result