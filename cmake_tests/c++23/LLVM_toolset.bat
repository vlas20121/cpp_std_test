::https://prereleases.llvm.org/win-snapshots/LLVM-12.0.0-6923b0a7-win64.exe
::https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download
set toolset=G:/PF/LLVM/bin/
set cmake=G:/PF/CMake/bin
set CC=%toolset%clang.exe
set CXX=%toolset%clang++.exe
set mingw_make=G:/PF/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/
set path=%toolset%;%mingw_make%;%cmake%
