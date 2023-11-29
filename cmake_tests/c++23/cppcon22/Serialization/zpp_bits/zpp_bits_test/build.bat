call ../../../../setup_toolset.bat
mkdir build
cd build
cmake  -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=%CXX% -B bin .. > cmake.log 2>&1
cmake --build bin > build.log 2>&1
bin\test.exe
