//
// Created by balazs on 6/19/22.
//

#include "../include/instructions.h"
#include "../include/display.h"
#include "../include/input.h"
#include "../include/memory.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>


void cls()
{
    disp_clear();
    program_counter += 2;
}


void ret()
{
    program_counter = stack[stack_pointer--] + 2;
}


void jmp(uint16_t addr)
{
    program_counter = addr;
}


void call(uint16_t addr)
{
    stack_pointer++;
    stack[stack_pointer] = program_counter;
    program_counter = addr;
}


void se_vx_byte(uint8_t x, uint8_t kk)
{
    if (data_register[x] == kk)
    {
        program_counter += 2;
    }

    program_counter += 2;
}


void sne_vx_byte(uint8_t x, uint8_t kk)
{
    if (data_register[x] != kk)
    {
        program_counter += 2;
    }

    program_counter += 2;
}


void se_vx_vy(uint8_t x, uint8_t y)
{
    if (data_register[x] == data_register[y])
    {
        program_counter += 2;
    }

    program_counter += 2;
}


void ld_vx_byte(uint8_t x, uint8_t kk)
{
    data_register[x] = kk;
    program_counter += 2;
}


void add_vx_byte(uint8_t x, uint8_t kk)
{
    data_register[x] += kk;
    program_counter += 2;
}


void ld_vx_vy(uint8_t x, uint8_t y)
{
    data_register[x] = data_register[y];
    program_counter += 2;
}


void or_vx_vy(uint8_t x, uint8_t y)
{
    data_register[x] |= data_register[y];
    program_counter += 2;
}


void and_vx_vy(uint8_t x, uint8_t y)
{
    data_register[x] &= data_register[y];
    program_counter += 2;
}


void xor_vx_vy(uint8_t x, uint8_t y)
{
    data_register[x] ^= data_register[y];
    program_counter += 2;
}


void add_vx_vy(uint8_t x, uint8_t y)
{
    uint16_t result = data_register[x] + data_register[y];
    if (result <= 0xFF)
    {
        data_register[x] = result;
    }
    else
    {
        data_register[x] = result & 0xFF; // logical AND with lower 8 bits (255)
    }

    program_counter += 2;
}


void sub_vx_vy(uint8_t x, uint8_t y)
{
    data_register[0xF] = data_register[x] > data_register[y]; // VF set to 1 if !BORROW -> VF set to 1 if Vx > Vy
    data_register[x] -= data_register[y];
    program_counter += 2;
}


void shr_vx(uint8_t x)
{
    data_register[0xF] = (data_register[x] % 2 == 1); // VF is set to 1 if tmp's least significant bit is 1 (number is odd)
    data_register[x] = data_register[x] >> 1; // divide by 2 by shifting right
    program_counter += 2;
}


void subn_vx_vy(uint8_t x, uint8_t y)
{
    data_register[0xF] = data_register[y] > data_register[x]; // VF set to 1 if !BORROW -> VF set to 1 if Vy > Vx
    data_register[x] = data_register[y] - data_register[x];
    program_counter += 2;
}


void shl_vx(uint8_t x)
{
    data_register[0xF] = (data_register[x] & 0x80) == 0x80;
    data_register[x] = data_register[x] << 2;
    program_counter += 2;
}


void sne_vx_vy(uint8_t x, uint8_t y)
{
    if (data_register[x] != data_register[y])
    {
        program_counter += 2;
    }

    program_counter += 2;
}


void ld_i_addr(uint16_t addr)
{
    I_register = addr;
    program_counter += 2;
}


void jmp_v0_addr(uint16_t addr)
{
    program_counter = data_register[0] + addr;
}


int first_random = 1;
void rnd_vx_kk(uint8_t x, uint8_t kk)
{
    if (first_random) {
        srand(time(0));
        first_random = 0;
    }

    data_register[x] = (rand() % 256) | kk;
    program_counter += 2;
}


void drw_vx_vy_nbbl(uint8_t x, uint8_t y, uint8_t n)
{
    data_register[0xF] = 0; // set collision to false

    uint8_t vx = data_register[x];
    uint8_t vy = data_register[y];
    int height = n;

    for(int _y = 0; _y < height; _y++){
        uint8_t pixel = memory[I_register + _y];
        for(int _x = 0; _x < 8; _x++){
            if(pixel & (0x80 >> _x)){
                uint8_t current = disp_get_px((_x + vx) % COLUMNS, (_y + vy) % ROWS);
                if (current) data_register[0xF] = 1;
                disp_set_px(current ^ pixel, (_x + vx) % COLUMNS, (_y + vy) % ROWS);
            }
        }
    }
    program_counter += 2;
}


void skp_vx(uint8_t x)
{
    if (keypad_state[data_register[x]])
    {
        program_counter += 2;
    }

    program_counter += 2;
}


void sknp_vx(uint8_t x)
{
    if (!keypad_state[data_register[x]])
    {
        program_counter += 2;
    }

    program_counter += 2;
}


void ld_vx_dt(uint8_t x)
{
    data_register[x] = delay_timer;
    program_counter += 2;
}


void ld_vx_k(uint8_t x)
{
    uint8_t index = 0;
    while (index < KEYPADS && !keypad_state[index]) {
        index++;
    }

    if (index < KEYPADS)
    {
        data_register[x] = index;
        program_counter += 2; // only jump to next instruction if key was pressed
    }
}


void ld_dt_vx(uint8_t x)
{
    delay_timer = data_register[x];
    program_counter += 2;
}


void ld_st_vx(uint8_t x)
{
    sound_timer = data_register[x];
    program_counter += 2;
}


void add_i_vx(uint8_t x)
{
    I_register += data_register[x];
    program_counter += 2;
}


void ld_f_vx(uint8_t x)
{
    I_register = data_register[x] * 5;
    program_counter += 2;
}


void ld_b_vx(uint8_t x)
{
    memory[I_register] = data_register[x] / 100;
    memory[I_register + 1] = (data_register[x] / 10) % 10;
    memory[I_register + 2] = data_register[x] % 10;
    program_counter += 2;
}


void ld_i_vx(uint8_t x)
{
    for (int i = 0; i < 0xF; i++)
    {
        memory[I_register + i] = data_register[i];
    }
    program_counter += 2;
}


void ld_vx_i(uint8_t x)
{
    for (int i = 0; i < 0xF; i++)
    {
        data_register[i] = memory[I_register + i];
    }
    program_counter += 2;
}