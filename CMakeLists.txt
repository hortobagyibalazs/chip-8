cmake_minimum_required(VERSION 3.22)
project(chip_8 C)

set(CMAKE_C_STANDARD 99)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(chip_8 main.c display.h display.c cpu.h cpu.c instructions.h)
target_link_libraries(chip_8 OpenGL::GL GLUT::GLUT)