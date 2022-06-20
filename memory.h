//
// Created by balazs on 6/19/22.
//

#ifndef CHIP_8_MEMORY_H
#define CHIP_8_MEMORY_H

#define MEMORY_CAPACITY 4096
#define STACK_CAPACITY 16
#define REGISTER_COUNT 16

#include <stdint.h>

uint8_t memory[MEMORY_CAPACITY];
uint16_t stack[STACK_CAPACITY];

uint16_t I_register; // used to store memory addresses
uint8_t data_register[REGISTER_COUNT];
uint16_t program_counter;
uint8_t stack_pointer;

uint8_t delay_timer;
uint8_t sound_timer;

#endif //CHIP_8_MEMORY_H
