cmake_minimum_required(VERSION 3.10)

project(Pac-Man)

file(GLOB_RECURSE SOURCES "Pac-Man/*.cpp")
add_executable(pacman.x ${SOURCES})

target_link_libraries(pacman.x 
    PRIVATE 
        sfml-graphics 
        sfml-window 
        sfml-system
)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/assets)

file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)