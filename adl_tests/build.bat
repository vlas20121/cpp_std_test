mkdir build
cd build
del Debug\test.exe
cmake  .. > cmake.log 2>&1
cmake --build . > build.log 2>&1
Debug\test.exe
