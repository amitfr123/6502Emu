#include "interpreter.h"

// addr modes
uint16_t accum_addr(cpu_t * cpu, uint8_t opcode);
uint16_t imm_addr(cpu_t * cpu, uint8_t opcode);
uint16_t absolute_addr(cpu_t * cpu, uint8_t opcode);
uint16_t zp_addr(cpu_t * cpu, uint8_t opcode);
uint16_t i_zp_x_addr(cpu_t * cpu, uint8_t opcode);
uint16_t i_zp_y_addr(cpu_t * cpu, uint8_t opcode);
uint16_t i_absolute_addr_x(cpu_t * cpu, uint8_t opcode);
uint16_t i_absolute_addr_y(cpu_t * cpu, uint8_t opcode);
uint16_t implied_addr(cpu_t * cpu, uint8_t opcode);
uint16_t relative_addr(cpu_t * cpu, uint8_t opcode);
uint16_t i_indirect_addr(cpu_t * cpu, uint8_t opcode);
uint16_t indirect_i_addr(cpu_t * cpu, uint8_t opcode);
uint16_t indirect_addr(cpu_t * cpu, uint8_t opcode);

// this is used for functions directly targeting the accumulator so no addr is needed
uint16_t accum_addr(cpu_t * cpu, uint8_t opcode)
{
    return 0;
}

uint16_t imm_addr(cpu_t * cpu, uint8_t opcode)
{
    return cpu->pc++;
}

uint16_t absolute_addr(cpu_t * cpu, uint8_t opcode)
{
    uint16_t lo = cpu_read(*cpu,  cpu->pc++);
    uint16_t hi = cpu_read(*cpu,  cpu->pc++);
    return lo | (hi << sizeof(uint8_t));
}

uint16_t zp_addr(cpu_t * cpu, uint8_t opcode)
{
    return cpu_read(*cpu, cpu->pc++);
}

uint16_t i_zp_x_addr(cpu_t * cpu, uint8_t opcode)
{
    return (cpu_read(*cpu, cpu->pc++) + cpu->x) & 0x00ff;
}

uint16_t i_zp_y_addr(cpu_t * cpu, uint8_t opcode)
{
    return (cpu_read(*cpu, cpu->pc++) + cpu->y) & 0x00ff;
}

uint16_t i_absolute_addr_x(cpu_t * cpu, uint8_t opcode)
{
    uint16_t lo = cpu_read(*cpu,  cpu->pc++);
    uint16_t hi = cpu_read(*cpu,  cpu->pc++);
    uint16_t addr = 0;
    addr = lo | (hi << sizeof(uint8_t)) + cpu->x;
    if ((addr & 0xff00) != hi)
    {
        cpu->cycles++;
    }
    return addr;
}

uint16_t i_absolute_addr_y(cpu_t * cpu, uint8_t opcode)
{
    uint16_t addr = 0;
    addr |= cpu_read(*cpu,  cpu->pc++);
    addr |=  (cpu_read(*cpu,  cpu->pc++) << sizeof(uint8_t));
    return addr + cpu->y;
}

uint16_t implied_addr(cpu_t * cpu, uint8_t opcode)
{
    return 0;
}

uint16_t relative_addr(cpu_t * cpu, uint8_t opcode)
{
    int8_t offset = cpu_read(*cpu,  cpu->pc++);
    return cpu->pc + offset;
}

uint16_t i_indirect_addr(cpu_t * cpu, uint8_t opcode)
{
    uint16_t zpg_addr = (cpu_read(*cpu, cpu->pc++) + cpu->x) & 0x00ff;
    uint16_t addr = 0;
    addr |= cpu_read(*cpu, zpg_addr++);
    addr |= (cpu_read(*cpu, zpg_addr) >> sizeof(uint8_t));
    return addr;
}
uint16_t indirect_i_addr(cpu_t * cpu, uint8_t opcode)
{
    uint16_t zpg_addr = cpu_read(*cpu, cpu->pc++);
    uint16_t addr = 0;
    addr |= cpu_read(*cpu, zpg_addr++);
    addr |= (cpu_read(*cpu, zpg_addr) << sizeof(uint8_t));
    return addr + cpu->y;
}
uint16_t indirect_addr(cpu_t * cpu, uint8_t opcode)
{
    uint16_t ind_addr = 0;
    uint16_t addr = 0;
    ind_addr |= cpu_read(*cpu, cpu->pc++);
    ind_addr |= cpu_read(*cpu, cpu->pc++) << sizeof(uint8_t);
    addr |= cpu_read(*cpu, ind_addr++);
    addr |= (cpu_read(*cpu, ind_addr) << sizeof(uint8_t));
    return addr;
}