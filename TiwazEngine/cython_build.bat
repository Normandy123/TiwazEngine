@echo off
title Build Tiwaz Cython
cd C:\Users\Oli\Documents\Visual Studio 2017\Projects\TiwazEngineDev\TiwazEngine
python setup.py build_ext --inplace --compiler=msvc
pause