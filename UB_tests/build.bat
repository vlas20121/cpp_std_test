mkdir build
cd build
del Release\test.exe
cmake .. > cmake.log 2>&1
cmake --build  . --config Release > build.log 2>&1
Release\test.exe
