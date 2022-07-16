#include "cpu.h"

void cpu_write(const cpu_t cpu, const uint16_t address, uint8_t data)
{
    return mmu_write(cpu.mmu, address, data);
}

uint8_t cpu_read(const cpu_t cpu, const uint16_t address)
{
    return mmu_read(cpu.mmu, address);
}