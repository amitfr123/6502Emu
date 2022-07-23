#include "../include/Mmu.hpp"

void Mmu::MmuWrite(const uint16_t address, const uint8_t data)
{
    for (auto &target : _memoryMapper)
    {  
        if (target.offset + target.size < address && address >= target.offset)
        {
            target.writeFunc(address, data);
        }
    }
}

uint8_t Mmu::MmuRead(const uint16_t address)
{
    for (auto &target : _memoryMapper)
    {  
        if (target.offset + target.size < address && address >= target.offset)
        {
            return target.readFunc(address);
        }
    }
    return 0; // If we reach here read operation failed
}

void Mmu::RamWrite(const uint16_t address, const uint8_t data)
{
    _ram[address % TRUE_RAM_SIZE] = data;
}

uint8_t Mmu::RamRead(const uint16_t address)
{
    return _ram[address % TRUE_RAM_SIZE];
}