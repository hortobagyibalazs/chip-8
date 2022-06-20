#include "memory.h"
#include <stdio.h>
#include <GL/glut.h>
#include "../include/memory.h"
#include "input.h"
#include "display.h"

int main(int argc, char** argv)
{
    load_rom("/home/balazs/projects/chip-8/roms/Airplane.ch8");

    glutInit(&argc, argv);

    disp_init();
    keyboard_init();

    glutMainLoop();
    return 0;
}
