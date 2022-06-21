//
// Created by balazs on 6/20/22.
//

#ifndef CHIP_8_INPUT_H
#define CHIP_8_INPUT_H

#define KEYPADS 16 // number of keypads

extern int keypad_state[KEYPADS];

void keyboard_init();
void key_down(unsigned char, int, int);
void key_up(unsigned char, int, int);
void clear_keypad_state();

#endif //CHIP_8_INPUT_H
