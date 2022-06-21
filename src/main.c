#include "memory.h"
#include <GL/glut.h>
#include "input.h"
#include "display.h"
#include "cpu.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    load_font_set();
    load_rom("/home/balazs/projects/chip-8/roms/test_opcode.ch8");
    disp_init();
    keyboard_init();
    cpu_init();

    glutMainLoop();
    return 0;
}
