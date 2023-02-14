cmake_minimum_required(VERSION 3.25.1)

project(gui LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake"
#   CACHE STRING "vcpkg toolchain file" FORCE)

add_subdirectory(app) 