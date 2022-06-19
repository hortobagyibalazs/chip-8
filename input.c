//
// Created by balazs on 6/20/22.
//

#include "input.h"
#include <GL/glut.h>
#include <stdio.h>

int get_keypad_for_char(unsigned int ch);
void set_key_value(unsigned char ch, int val);

int key_state[KEYPAD_NUM];

void keyboard_init()
{
    glutKeyboardFunc(key_down);
    glutKeyboardUpFunc(key_up);
}

void key_up(unsigned char ch, int x, int y)
{
    set_key_value(ch, 0);
}

void key_down(unsigned char ch, int x, int y)
{
    set_key_value(ch, 1);
}

int get_keypad_for_char(unsigned int ch)
{
    char* seq = "1234qwerasdfyxcv";
    int index = 0;
    while (seq[index] != 0 && seq[index] != ch)
    {
        index++;
    }

    if (seq[index])
    {
        return index;
    }
    else
    {
        return -1;
    }
}

void set_key_value(unsigned char ch, int val)
{
    int index = get_keypad_for_char(ch);

    if (index != -1)
    {
        key_state[index] = val;
    }
}