cmake_minimum_required(VERSION 3.10)
project(Asteroids)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX)
    set(SFML_PATH "/home/Projects/Programming/C++/SFML-2.6.2") 
elseif(WIN32)
    set(SFML_PATH "C:/Develop/SFML-2.6.2")
endif()

add_definitions(-DSFML_STATIC)

include_directories("${SFML_PATH}/include")
link_directories("${SFML_PATH}/lib")

file(GLOB SOURCES "Asteroids/*.cpp")

add_executable(Asteroids ${SOURCES})

if(WIN32)
    # Windows Static Linking
    # Reihenfolge ist wichtig: Erst Graphics, dann Window, dann System
    target_link_libraries(Asteroids
        sfml-graphics-s 
        sfml-window-s 
        sfml-system-s
        sfml-main
        opengl32 
        winmm 
        gdi32 
        freetype
    )
elseif(UNIX)
    # Linux Static Linking
    # Hier müssen alle Abhängigkeiten von SFML manuell gelistet werden,
    # da wir keine Shared Libs nutzen, die das automatisch machen.
    target_link_libraries(Asteroids
        sfml-graphics-s
        sfml-window-s
        sfml-system-s
        
        #System-Abhängigkeiten (müssen auf Linux installiert sein: libudev-dev, libx11-dev, etc.)
        udev 
        GL 
        X11 
        X11-xcb 
        xcb 
        Xrandr
        Xcursor
        freetype 
        openal 
        vorbisenc 
        vorbisfile 
        vorbis 
        ogg 
        FLAC
        pthread
        dl
    )
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/assets")
    file(COPY "${CMAKE_SOURCE_DIR}/assets" DESTINATION "${CMAKE_BINARY_DIR}")
endif()