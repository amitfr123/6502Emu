#include "mmu.h"
#include <stdlib.h>
#include <stdio.h>

int mmu_init(mmu_t * mmu)
{
    int retval = 0;
   
    if (mmu->ram = (uint8_t *)calloc(TRUE_RAM_SIZE, sizeof(uint8_t)) == NULL)
    {
        // retval allready set
        printf("RAM allocation failed\n");
    }
}

// data is uint 8 because thats the data bus size
void mmu_write(const mmu_t mmu, const uint16_t address, uint8_t data)
{
    if (address < RAM_RANGE)
    {
        mmu.ram[address % TRUE_RAM_SIZE] = data;
    }
}

uint8_t mmu_read(const mmu_t mmu, const uint16_t address)
{
    uint8_t data;
    if (address < RAM_RANGE)
    {
        data = mmu.ram[address % TRUE_RAM_SIZE];
    }
}