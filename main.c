#include "display.h"
#include "input.h"
#include <GL/glut.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    disp_init();
    keyboard_init();

    glutMainLoop();
    return 0;
}
