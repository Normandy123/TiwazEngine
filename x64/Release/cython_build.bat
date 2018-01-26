echo off
title Cython Build
cd C:\Users\Oli\Documents\Visual Studio 2017\Projects\TiwazEngineDev\x64\Release
python setup.py build_ext --inplace --compiler=msvc
pause