//
// Created by balazs on 6/18/22.
//

#include "display.h"
#include <GL/glut.h>

uint8_t framebuffer[COLUMNS][ROWS];

int window_width = 600;
int window_height = 600;

void resize(int, int);

void disp_init(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    //glutInitWindowPosition(POS);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("Chip-8 Emulator");
    glutReshapeFunc(resize);

    glutDisplayFunc(disp_draw);
    glutMainLoop();
}

void disp_draw()
{
    glutSwapBuffers();
}

void disp_set_px(uint8_t val, int x, int y)
{

}

uint8_t disp_get_px(int x, int y)
{

}

void resize(int w, int h)
{
    window_width = w;
    window_height = h;
}