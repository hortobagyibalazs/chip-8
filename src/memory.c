//
// Created by balazs on 6/20/22.
//

#include "../include/memory.h"
#include <stdio.h>
#include <string.h>

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