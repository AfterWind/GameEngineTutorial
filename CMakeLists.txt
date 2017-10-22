cmake_minimum_required(VERSION 3.8)
project(GameEngineTutorialCode)

set(CMAKE_C_STANDARD 11)
set(SOURCE_FILES main.c)

include(FindPkgConfig)

find_package(OpenGL)
find_package(SDL2)
find_package(GLEW)
find_package(KAZMATH)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

string(REPLACE "  -mwindows" "" SDL2_LIBRARIES ${SDL2_LIBRARIES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${KAZMATH_LIBRARIES} ${SDL2IMAGE_LIBRARIES})