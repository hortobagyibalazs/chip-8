cmake_minimum_required(VERSION 3.22)
project(chip_8 C)

set(CMAKE_C_STANDARD 99)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(chip_8
        src/main.c
        src/memory.c
        src/display.c
        src/cpu.c
        src/instructions.c
        src/input.c)

target_include_directories(chip_8 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_directories(chip_8 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(chip_8 OpenGL::GL GLUT::GLUT)
