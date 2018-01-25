# distutils: language = c++
# distutils: extra_compile_args = /std:c++17
# distutils: sources = [engine_object.cpp, counter.cpp, message_system.cpp, engine_vars.cpp, object_system.cpp,]

cdef extern from "engine_object.h" namespace "Tiwaz":
	cdef cppclass EngineObject:
		EngineObject() except +
		void Init()
		void Update()
		void Exit()
		void SetObjectID(const unsigned long long & ID)
		const unsigned long long object_ID()
		
cdef extern from "object_system.h" namespace "Tiwaz::ObjectSystem":
	cdef cppclass ObjectManager:
		ObjectManager() except +
		const unsigned long long AddObject(EngineObject* object)

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
		
cdef class PyObjectManager:
	cdef ObjectManager* c_object_manager
	def __cinit__(self):
		self.c_object_manager = new ObjectManager()
	def __dealloc__(self):
		del self.c_object_manager
	def add_object(self, object : PyEngineObject): 
		return self.c_object_manager.AddObject(object.c_engineobject)
	
cpdef void create_objects(unsigned int count, manager : PyObjectManager):
	cdef unsigned int i = 0
	cdef EngineObject* temp	
	for i in range(count):	
		temp = new EngineObject()
		manager.c_object_manager.AddObject(temp)