//
// Created by balazs on 6/18/22.
//

#include "../include/cpu.h"
#include "../include/instructions.h"
#include "memory.h"
#include "input.h"
#include <stdio.h>
#include <GL/glut.h>

int del = CPU_FREQUENCY / DELAY_TIMER_FREQUENCY;
int sound = CPU_FREQUENCY / SOUND_TIMER_FREQUENCY;

int current_del;
int current_sound;

void cpu_init()
{
    program_counter = 0x200;
    glutTimerFunc(0, cycle, 0);
}

void cycle()
{
    uint16_t first_byte = memory[program_counter];
    uint16_t second_byte = memory[program_counter + 1];
    uint16_t instr = second_byte + (first_byte << 8);

    if (instr == 0x00E0)
    {
        cls();
    }
    else if (instr == 0x00EE)
    {
        ret();
    }
    else if ((instr & 0xF000) == 0x1000)
    {
        uint16_t addr = instr & 0x0FFF;
        jmp(addr);
    }
    else if ((instr & 0xF000) == 0x2000)
    {
        uint16_t addr = instr & 0x0FFF;
        call(addr);
    }
    else if ((instr & 0xF000) == 0x3000)
    {
        uint8_t reg = (instr & 0x0F00) >> 8;
        uint16_t byte = instr & 0x00FF;
        se_vx_byte(reg, byte);
    }
    else if ((instr & 0xF000) == 0x4000)
    {
        uint8_t reg = (instr & 0x0F00) >> 8;
        uint16_t byte = instr & 0x00FF;
        sne_vx_byte(reg, byte);
    }
    else if ((instr & 0xF00F) == 0x5000)
    {
        uint8_t reg_x = (instr & 0x0F00) >> 8;
        uint8_t reg_y = (instr & 0x00F0) >> 4;
        se_vx_vy(reg_x, reg_y);
    }
    else if ((instr & 0xF000) == 0x6000)
    {
        uint8_t reg = (instr & 0x0F00) >> 8;
        uint16_t byte = instr & 0x00FF;
        ld_vx_byte(reg, byte);
    }
    else if ((instr & 0xF000) == 0x7000)
    {
        uint8_t reg = (instr & 0x0F00) >> 8;
        uint16_t byte = instr & 0x00FF;
        add_vx_byte(reg, byte);
    }
    else if ((instr & 0xF00F) == 0x8000)
    {
        uint8_t reg_x = (instr & 0x0F00) >> 8;
        uint16_t reg_y = (instr & 0x00F0) >> 4;
        ld_vx_vy(reg_x, reg_y);
    }
    else if ((instr & 0xF00F) == 0x8001)
    {
        uint8_t reg_x = (instr & 0x0F00) >> 8;
        uint16_t reg_y = (instr & 0x00F0) >> 4;
        or_vx_vy(reg_x, reg_y);
    }
    else if ((instr & 0xF00F) == 0x8002)
    {
        uint8_t reg_x = (instr & 0x0F00) >> 8;
        uint16_t reg_y = (instr & 0x00F0) >> 4;
        and_vx_vy(reg_x, reg_y);
    }
    else if ((instr & 0xF00F) == 0x8003)
    {
        uint8_t reg_x = (instr & 0x0F00) >> 8;
        uint16_t reg_y = (instr & 0x00F0) >> 4;
        xor_vx_vy(reg_x, reg_y);
    }
    else if ((instr & 0xF00F) == 0x8004)
    {
        uint8_t reg_x = (instr & 0x0F00) >> 8;
        uint16_t reg_y = (instr & 0x00F0) >> 4;
        add_vx_vy(reg_x, reg_y);
    }
    else if ((instr & 0xF00F) == 0x8005)
    {
        uint8_t reg_x = (instr & 0x0F00) >> 8;
        uint16_t reg_y = (instr & 0x00F0) >> 4;
        sub_vx_vy(reg_x, reg_y);
    }
    else if ((instr & 0xF00F) == 0x8006)
    {
        uint8_t reg = (instr & 0x0F00) >> 8;
        shr_vx(reg);
    }
    else if ((instr & 0xF00F) == 0x8007)
    {
        uint8_t reg_x = (instr & 0x0F00) >> 8;
        uint16_t reg_y = (instr & 0x00F0) >> 4;
        subn_vx_vy(reg_x, reg_y);
    }
    else if ((instr & 0xF00F) == 0x800E)
    {
        uint8_t reg = (instr & 0x0F00) >> 8;
        shl_vx(reg);
    }
    else if ((instr & 0xF00F) == 0x9000)
    {
        uint8_t reg_x = (instr & 0x0F00) >> 8;
        uint8_t reg_y = (instr & 0x00F0) >> 4;
        sne_vx_vy(reg_x, reg_y);
    }
    else if ((instr & 0xF000) == 0xA000)
    {
        uint16_t addr = instr & 0x0FFF;
        ld_i_addr(addr);
    }
    else if ((instr & 0xF000) == 0xB000)
    {
        uint16_t addr = instr & 0x0FFF;
        jmp_v0_addr(addr);
    }
    else if ((instr & 0xF000) == 0xC000)
    {
        uint8_t reg_x = (instr & 0x0F00) >> 8;
        uint16_t byte = instr & 0x00FF;
        rnd_vx_kk(reg_x, byte);
    }
    else if ((instr & 0xF000) == 0xD000)
    {
        uint8_t reg_x = (instr & 0x0F00) >> 8;
        uint8_t reg_y = (instr & 0x00F0) >> 4;
        uint16_t nibble = instr & 0x000F;
        drw_vx_vy_nbbl(reg_x, reg_y, nibble);
    }
    else if ((instr & 0xF0FF) == 0xE09E)
    {
        uint8_t reg = (instr & 0x0F00) >> 8;
        skp_vx(reg);
    }
    else if ((instr & 0xF0FF) == 0xE0A1)
    {
        uint8_t reg = (instr & 0x0F00) >> 8;
        sknp_vx(reg);
    }
    else if ((instr & 0xF0FF) == 0xF007)
    {
        uint8_t reg = (instr & 0x0F00) >> 8;
        ld_vx_dt(reg);
    }
    else if ((instr & 0xF0FF) == 0xF00A)
    {
        uint8_t reg = (instr & 0x0F00) >> 8;
        ld_vx_k(reg);
    }
    else if ((instr & 0xF0FF) == 0xF015)
    {
        uint8_t reg = (instr & 0x0F00) >> 8;
        ld_dt_vx(reg);
    }
    else if ((instr & 0xF0FF) == 0xF018)
    {
        uint8_t reg = (instr & 0x0F00) >> 8;
        ld_st_vx(reg);
    }
    else if ((instr & 0xF0FF) == 0xF01E)
    {
        uint8_t reg = (instr & 0x0F00) >> 8;
        add_i_vx(reg);
    }
    else if ((instr & 0xF0FF) == 0xF029)
    {
        uint8_t reg = (instr & 0x0F00) >> 8;
        ld_f_vx(reg);
    }
    else if ((instr & 0xF0FF) == 0xF033)
    {
        uint8_t reg = (instr & 0x0F00) >> 8;
        ld_b_vx(reg);
    }
    else if ((instr & 0xF0FF) == 0xF055)
    {
        uint8_t reg = (instr & 0x0F00) >> 8;
        ld_i_vx(reg);
    }
    else if ((instr & 0xF0FF) == 0xF065)
    {
        uint8_t reg = (instr & 0x0F00) >> 8;
        ld_vx_i(reg);
    }

    if (delay_timer > 0) {
        delay_timer--;
    }

    if (sound_timer > 0) {
        sound_timer--;
    }

    glutTimerFunc(1, cycle, 0);
}