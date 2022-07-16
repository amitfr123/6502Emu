#ifndef INTERPRETER
#define INTERPRETER

#include <stdint.h>
#include "cpu.h"

typedef enum
{
    ACCUM, // Operation on the accumulator
    IMM, // Second byte contains the opeand with no further memory addresing required
    ABSOLUTE, // Second and third bytes contain a full 16 bit address
    ZP, // Zero page instruction
    I_ZP_X, // Uses the zero page addressing and the x registers
    I_ZP_Y, // Uses the zero page addressing and the y registers
    I_ABSOLUTE_X, // Absolute addressing that also uses the x registers
    I_ABSOLUTE_Y, // Absolute addressing that also uses the y registers
    IMPLIED, // The address containing the operand is implicitly stated in the operation code
    RELATIVE, // Used only in branch instructions and establishes a destination for the conditional branch
    I_INDIRECT, // The second byte is added to the x register and the result is a zero page address. From the zero page you take the effective address is the next 2 bytes.
    INDIRECT_I, // The second byte is added to the y register and the result is a zero page address. From the zero page you take the effective address is the next 2 bytes.
    INDIRECT, // The second and third contain a full 16 bit address. From this address you take the effective address is the next 2 bytes.
}addr_mode_e;

typedef struct
{
    uint8_t opcode;
    uint8_t size;
    uint8_t mechine_cycles;
    addr_mode_e addr_mode;
    uint16_t (*addr_mode_func)(cpu_t cpu);
    void (*instruction_acction)(cpu_t cpu);
} instruction_t;


#endif // INTERPRETER
