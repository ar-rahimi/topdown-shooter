cmake_minimum_required(VERSION 3.8)
project(GroepH)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${GroepH_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(BOX2D REQUIRED)

find_path(BOX2D_INCLUDE_DIRS Box2D/include/Box2D/Box2D.h)
find_library(BOX2D_LIBRARIES Box2   D/lib/libBox2D.a)
file(GLOB GroepH_SRC
        "*.h"
        "*.cpp"
        )
if(BOX2D_LIBRARIES)
    MESSAGE("1")
else()
    MESSAGE("2")
endif()

if(BOX2D_INCLUDE_DIRS)
    MESSAGE("11")
else()
    MESSAGE("22")
endif()
message(STATUS "Box2D:")
message(STATUS "  - include dirs: ${BOX2D_INCLUDE_DIR}")
message(STATUS "  - libraries: ${BOX2D_LIBRARIES}")

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${BOX2D_INCLUDE_DIR} src/game/headers src/engine/headers content include)
set(SOURCE_FILES
        content/sprites/PLACEHOLDER.txt
        src/engine/headers/animatedobject.h
        src/engine/headers/assetsmanager.h
        src/engine/headers/inputmanager.h
        src/engine/headers/moveableobject.h
        src/engine/headers/rendermanager.h
        src/engine/headers/spriteobject.h
        src/engine/source/animatedobject.cpp
        src/engine/source/assetsmanager.cpp
        src/engine/source/inputmanager.cpp
        src/engine/source/moveableobject.cpp
        src/engine/source/rendermanager.cpp
        src/engine/source/spriteobject.cpp
        src/game/headers/bullet.h
        src/game/headers/game.h
        src/game/headers/globals.h
        src/game/headers/helper.h
        src/game/headers/player.h
        src/game/source/bullet.cpp
        src/game/source/game.cpp
        src/game/source/helper.cpp
        src/game/source/player.cpp
        src/game/main.cpp
        include
        ${BOX2D_INCLUDE_DIR}
        src/game/headers/wall.h src/game/source/wall.cpp src/engine/headers/contactlistener.h src/engine/source/contactlistener.cpp)

add_executable(GroepH ${SOURCE_FILES} ${GroepH_SRC})

target_link_libraries(GroepH ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${BOX2D_LIBRARY_RELEASE})#${BOX2D_LIBRARY} ${BOX2D_LIBRARY_RELEASE} ${BOX2D_LIBRARY_DEBUG})