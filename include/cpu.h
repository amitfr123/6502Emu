#ifndef CPU
#define CPU

#include <stdint.h>
#include "mmu.h"


#define SET_FLAG(flags, mask) flags |= mask
#define CLR_FLAG(flags, mask) flags &= ~(mask)

#define CARRY_FLAG_MASK 0x01
#define ZERO_FLAG_MASK 0x02
#define INTERRUPT_DISABLE_FLAG_MASK 0x04
#define DECIMAL_MODE_FLAG_MASK 0x06
#define BREAK_COMMAND_FLAG_MASK 0x10
#define OVERFLOW_FLAG_MASK 0x40
#define NEGATIVE_FLAG_MASK 0x80

#define SET_CARRY_FLAG(cpu) SET_FLAG(cpu.p, CARRY_FLAG_MASK)
#define CLR_CARRY_FLAG(cpu) CLR_FLAG(cpu.p, CARRY_FLAG_MASK)

#define SET_ZERO_FLAG(cpu) SET_FLAG(cpu.p, ZERO_FLAG_MASK)
#define CLR_ZERO_FLAG(cpu) CLR_FLAG(cpu.p, ZERO_FLAG_MASK)

#define SET_INTERRUPT_DISABLE_FLAG(cpu) SET_FLAG(cpu.p, INTERRUPT_DISABLE_FLAG_MASK)
#define CLR_INTERRUPT_DISABLE_FLAG(cpu) CLR_FLAG(cpu.p, INTERRUPT_DISABLE_FLAG_MASK)

#define SET_DECIMAL_MODE_FLAG(cpu) SET_FLAG(cpu.p, DECIMAL_MODE_FLAG_MASK)
#define CLR_DECIMAL_MODE_FLAG(cpu) CLR_FLAG(cpu.p, DECIMAL_MODE_FLAG_MASK)

#define SET_BREAK_COMMAND_FLAG(cpu) SET_FLAG(cpu.p, BREAK_COMMAND_FLAG_MASK)
#define CLR_BREAK_COMMAND_FLAG(cpu) CLR_FLAG(cpu.p, BREAK_COMMAND_FLAG_MASK)

#define SET_OVERFLOW_FLAG(cpu) SET_FLAG(cpu.p, OVERFLOW_FLAG_MASK)
#define CLR_OVERFLOW_FLAG(cpu) CLR_FLAG(cpu.p, OVERFLOW_FLAG_MASK)

#define SET_NEGATIVE_FLAG(cpu) SET_FLAG(cpu.p, NEGATIVE_FLAG_MASK)
#define CLR_NEGATIVE_FLAG(cpu) CLR_FLAG(cpu.p, NEGATIVE_FLAG_MASK)

// The cpu registers
typedef struct 
{
    uint16_t pc; //program counter
    uint8_t sp; //stack
    uint8_t a; //accumulator
    uint8_t x; //index
    uint8_t y; //index
    uint8_t p; //flags
    mmu_t mmu; //the mmu
    size_t cycles;
}cpu_t;

// Shoved in the stack when there is an interrupt
typedef struct 
{
    uint16_t pc; //program counter
    uint8_t p; //flags
}cpu_save_state_t;

// data is uint 8 because thats the data bus size
void cpu_write(const cpu_t cpu, const uint16_t address, uint8_t data);

uint8_t cpu_read(const cpu_t cpu, const uint16_t address);

#endif CPU