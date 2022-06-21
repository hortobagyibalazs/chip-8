//
// Created by balazs on 6/18/22.
//

#ifndef CHIP_8_CPU_H
#define CHIP_8_CPU_H

#define CPU_FREQUENCY 500 // 500Hz CPU clock speed or 500 instructions per second
#define DELAY_TIMER_FREQUENCY 60
#define SOUND_TIMER_FREQUENCY 60

void cpu_init();
void cycle();

#endif //CHIP_8_CPU_H
