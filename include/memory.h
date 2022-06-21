//
// Created by balazs on 6/19/22.
//

#ifndef CHIP_8_MEMORY_H
#define CHIP_8_MEMORY_H

#define MEMORY_CAPACITY 4096
#define STACK_CAPACITY 16
#define REGISTER_COUNT 16

#include <stdint.h>

extern uint8_t memory[MEMORY_CAPACITY];
extern uint16_t stack[STACK_CAPACITY];

extern uint16_t I_register; // used to store memory addresses
extern uint8_t data_register[REGISTER_COUNT];
extern uint16_t program_counter;
extern uint8_t stack_pointer;

extern uint8_t delay_timer;
extern uint8_t sound_timer;

void load_font_set();
int load_rom(char* path);

#endif //CHIP_8_MEMORY_H
