//
// Created by balazs on 6/18/22.
//

#include "display.h"
#include <GL/glut.h>
#include <stdio.h>

uint8_t framebuffer[COLUMNS][ROWS];

int window_width = 900;
int window_height = 450;

void resize(int, int);
double device_to_normalized(double coord, double axis_size);

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
    double px_width = window_width / COLUMNS;
    double px_height = window_height / ROWS;

    glColor3f(1, 0, 0);

    for (int x = 0; x < COLUMNS; x++)
    {
        for (int y = 0; y < ROWS; y++)
        {
            if (framebuffer[x][y])
            {
                glColor3f(1, 1, 1);
            }
            else
            {
                glColor3f(0, 0, 0);
            }

            glRectd(
                    device_to_normalized(x * px_width, window_width),
                    device_to_normalized(window_height - (y * px_height), window_height) ,
                    device_to_normalized((x + 1) * px_width, window_width),
                    device_to_normalized(window_height - (y + 1) * px_height, window_height)
            );
        }
    }

    glutSwapBuffers();
}

void disp_set_px(uint8_t val, int x, int y)
{
    framebuffer[x][y] = val;
}

uint8_t disp_get_px(int x, int y)
{
    return framebuffer[x][y];
}

void resize(int w, int h)
{
    window_width = w;
    window_height = h;
}

double device_to_normalized(double coord, double axis_size)
{
    double halfAxis = axis_size / 2;

    return (coord / halfAxis) - 1;
}