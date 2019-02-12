cmake_minimum_required(VERSION 3.7)
project(VirtualFileSystem)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Structs.h Disco.cpp Disco.h Directorio.cpp Directorio.h BitMap.cpp BitMap.h)
add_executable(VirtualFileSystem ${SOURCE_FILES})