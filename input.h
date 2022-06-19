//
// Created by balazs on 6/20/22.
//

#ifndef CHIP_8_INPUT_H
#define CHIP_8_INPUT_H

#define KEYPAD_NUM 16 // number of keypads

void keyboard_init();
void key_down(unsigned char, int, int);
void key_up(unsigned char, int, int);

#endif //CHIP_8_INPUT_H
