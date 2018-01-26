# distutils: language = c++
# distutils: extra_compile_args = [/std:c++latest, /Ox]

cdef extern from "engine_object.h" namespace "Tiwaz":
	cdef cppclass EngineObject:
		EngineObject() except +
		void Init()
		void Update()
		void Exit()
		void SetObjectID(const unsigned long long & ID)
		const unsigned long long object_ID()

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
	def set_object_ID(self, const unsigned long long & ID):
		self.c_engineobject.SetObjectID(ID)
	def object_ID(self):
		return self.c_engineobject.object_ID()		

cdef extern from "engine.h" namespace "Tiwaz":
	int RunEngine()
	int ExitEngine()
	
cpdef int run_engine():
	return RunEngine()

cpdef int exit_engine():
	return ExitEngine()
	
cdef extern from "python_functions.h" namespace "Tiwaz::Python":
	const unsigned long long AddObject(EngineObject* obj)	
	
cpdef void create_objects(size_t count):
	cdef size_t i = 0
	cdef EngineObject* temp	
	for i in range(count):	
		temp = new EngineObject()
		AddObject(temp)