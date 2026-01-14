cmake_minimum_required(VERSION 3.10)

project(Pac-Man)

file(GLOB_RECURSE SOURCES "Pac-Man/*.cpp")
add_executable(Pac-Man ${SOURCES})

target_link_libraries(pacman.x 
    PRIVATE 
        sfml-graphics 
        sfml-window 
        sfml-system
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)