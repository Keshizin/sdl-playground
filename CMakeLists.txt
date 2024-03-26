#
# CMakeLists.txt for SDL Playground
#

cmake_minimum_required(VERSION 3.15)


#
# project name
#

project(sdl-playground)


#
# output filename
#

set(APP_EXE playground)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)


#
# including path for include
#

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/stb")


#
# adding executable
#

link_directories("${PROJECT_SOURCE_DIR}/lib")
add_executable(${APP_EXE} main.cpp)

target_link_libraries(${APP_EXE} SDL3)
