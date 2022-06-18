//
// Created by balazs on 6/18/22.
//

#ifndef CHIP_8_DISPLAY_H
#define CHIP_8_DISPLAY_H

#include <stdint.h>

#define COLUMNS 64
#define ROWS 32

extern int window_width;
extern int window_height;

void disp_init(int argc, char** argv);
void disp_draw();
void disp_clear();
void disp_set_px(uint8_t, int, int);
uint8_t disp_get_px(int, int);

#endif //CHIP_8_DISPLAY_H
