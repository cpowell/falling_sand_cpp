cmake_minimum_required(VERSION 3.30)
project(falling_sand)

set(CMAKE_CXX_STANDARD 20)

add_executable(falling_sand main.cpp Grid.cpp Particle.cpp)

find_package(raylib REQUIRED) # QUIET or REQUIRED
target_link_libraries(falling_sand PRIVATE raylib)
