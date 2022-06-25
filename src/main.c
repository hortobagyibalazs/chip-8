#include "memory.h"
#include <GL/glut.h>
#include <stdio.h>
#include "input.h"
#include "display.h"
#include "cpu.h"

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    load_font_set();
    load_rom(argv[1]);
    disp_init();
    keyboard_init();
    cpu_init();

    glutMainLoop();
    return 0;
}
