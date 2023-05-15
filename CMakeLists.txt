cmake_minimum_required(VERSION 3.20)

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" PROJ_VERSION)
string(STRIP "${PROJ_VERSION}" PROJ_VERSION)

project(function_plotter VERSION "${PROJ_VERSION}")

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
