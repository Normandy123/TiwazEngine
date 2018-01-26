from distutils.core import setup
from Cython.Build import cythonize

setup(
	name = "tiwaz_cython",
	version = "1.0",
	author = "Normandy123",
    ext_modules = cythonize("tiwaz_cython.pyx")
)