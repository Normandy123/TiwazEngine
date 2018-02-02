import tiwaz_cython

tiwaz_cython.run_engine()

x = tiwaz_cython.PyObjectManager()

x.add_object(tiwaz_cython.PyEngineObject())

tiwaz_cython.exit_engine()