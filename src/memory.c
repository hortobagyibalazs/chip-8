//
// Created by balazs on 6/20/22.
//

#include "../include/memory.h"
#include <stdio.h>
#include <string.h>

uint8_t memory[] = {};
uint16_t stack[] = {};

uint16_t I_register = 0; // used to store memory addresses
uint8_t data_register[] = {};
uint16_t program_counter = 0;
uint8_t stack_pointer = 0;

uint8_t delay_timer = 0;
uint8_t sound_timer = 0;

void load_rom(char* path)
{
    // TODO : Check if binary file size is bigger than available memory
    FILE* file = fopen(path, "rb");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    fread((memory + 0x200), size, 1, file);
    fclose(file);
}