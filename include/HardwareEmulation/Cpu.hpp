#pragma once

#include <map>
#include <unordered_map>
#include <vector>
#include <fstream>

#include "Mmu.hpp"

class Cpu {
public:
    Cpu(Mmu::WriteFunction mmu_write, Mmu::ReadFunction mmu_read);
    std::map<uint16_t, std::string> Disassemble();
private:
    static constexpr uint8_t CARRY_FLAG_MASK = 0x01;
    static constexpr uint8_t ZERO_FLAG_MASK = 0x02;
    static constexpr uint8_t INTERRUPT_DISABLE_FLAG_MASK = 0x04;
    static constexpr uint8_t DECIMAL_MODE_FLAG_MASK = 0x08;
    static constexpr uint8_t BREAK_COMMAND_FLAG_MASK = 0x10;
    static constexpr uint8_t RESERVED_FLAG_MASK = 0x20;
    static constexpr uint8_t OVERFLOW_FLAG_MASK = 0x40;
    static constexpr uint8_t NEGATIVE_FLAG_MASK = 0x80;

    static constexpr uint16_t ABORT_LSB = 0xfff8;
    static constexpr uint16_t ABORT_MSB = 0xfff9;
    static constexpr uint16_t COP_LSB = 0xfff4;
    static constexpr uint16_t COP_MSB = 0xfff5;
    static constexpr uint16_t NORMAL_IRQ_LSB = 0xfffe;
    static constexpr uint16_t NORMAL_IRQ_MSB = 0xffff;
    static constexpr uint16_t BRK_LSB = NORMAL_IRQ_LSB;
    static constexpr uint16_t BRK_MSB = NORMAL_IRQ_MSB;
    static constexpr uint16_t NMI_LSB = 0xfffa;
    static constexpr uint16_t NMI_MSB = 0xfffb;
    static constexpr uint16_t RESET_LSB = 0xfffc;
    static constexpr uint16_t RESET_MSB = 0xfffd;

    enum class IrqType
    {
        ABORT,
        COP,
        NORMAL_IRQ,
        BRK,
        NMI,
        RESET
    };

    enum class AMode
    {
        ACCUM, //Operation on the accumulator
        IMM, //Second byte contains the opeand with no further memory addresing required
        ABSOLUTE, //Second and third bytes contain a full 16 bit address
        ZP, //Zero page instruction
        I_ZP_X, //Uses the zero page addressing and the x registers
        I_ZP_Y, //Uses the zero page addressing and the y registers
        I_ABSOLUTE_X, //Absolute addressing that also uses the x registers
        I_ABSOLUTE_Y, //Absolute addressing that also uses the y registers
        IMPLIED, //The address containing the operand is implicitly stated in the operation code
        RELATIVE, //Used only in branch instructions and establishes a destination for the conditional branch
        I_INDIRECT, //The second byte is added to the x register and the result is a zero page address. From the zero page you take the effective address is the next 2 bytes.
        INDIRECT_I, //The second byte is added to the y register and the result is a zero page address. From the zero page you take the effective address is the next 2 bytes.
        INDIRECT //The second and third contain a full 16 bit address. From this address you take the effective address is the next 2 bytes.
    };

    enum class IType
    {
        ADC,
        AND,
        ASL,
        BCC,
        BCS,
        BEQ,
        BIT,
        BMI,
        BNE,
        BPL,
        BRK,
        BVC,
        BVS,
        CLC, 
        CLD, 
        CLI,
        CLV,
        CMP,
        CPX,
        CPY,
        DEC,
        DEX,
        DEY,
        EOR,
        INC,
        INX,
        INY,
        JMP,
        JSR,
        LDA,
        LDX,
        LDY,
        LSR,
        NOP,
        ORA,
        PHA,
        PHP,
        PLA,
        PLP,
        ROL,
        ROR,
        RTI,
        RTS,
        SBC,
        SEC,
        SED,
        SEI,
        STA,
        STX,
        STY,
        TAX,
        TAY,
        TSX,
        TXA,
        TXS,
        TYA,
        MIA // MIA represents every illegal instruction that wasn't implemented
    };

    struct Instruction 
    {
        IType type;
        AMode addrMode;
        uint8_t cycles;
    };

    using AddressFunction = std::function<uint16_t ()>;
    using InstructionFunction = std::function<void (const Instruction &)>;

    uint16_t pc; //program counter
    uint8_t sp; //stack
    uint8_t a; //accumulator
    uint8_t x; //index
    uint8_t y; //index
    uint8_t p; //flags
    size_t cycles;
    Mmu::WriteFunction _mmu_write;
    Mmu::ReadFunction _mmu_read;
    std::unordered_map<AMode, AddressFunction> _address_mode_mapper;
    std::unordered_map<IType, InstructionFunction> _instruction_type_mapper;
    std::unordered_map<IrqType, std::pair<uint16_t, uint16_t>> _irq_vector_map;
    std::vector<Instruction> _opcode_vector;

    std::vector<std::string> _amode_name_mapper = 
    {
        "ACCUM",
        "IMM",
        "ABSOLUTE",
        "ZP",
        "I_ZP_X",
        "I_ZP_Y",
        "I_ABSOLUTE_X",
        "I_ABSOLUTE_Y",
        "IMPLIED",
        "RELATIVE",
        "I_INDIRECT",
        "INDIRECT_I",
        "INDIRECT"
    };

    std::vector<std::string> _itype_name_mapper = 
    {
        "ADC",
        "AND",
        "ASL",
        "BCC",
        "BCS",
        "BEQ",
        "BIT",
        "BMI",
        "BNE",
        "BPL",
        "BRK",
        "BVC",
        "BVS",
        "CLC",
        "CLD",
        "CLI",
        "CLV",
        "CMP",
        "CPX",
        "CPY",
        "DEC",
        "DEX",
        "DEY",
        "EOR",
        "INC",
        "INX",
        "INY",
        "JMP",
        "JSR",
        "LDA",
        "LDX",
        "LDY",
        "LSR",
        "NOP",
        "ORA",
        "PHA",
        "PHP",
        "PLA",
        "PLP",
        "ROL",
        "ROR",
        "RTI",
        "RTS",
        "SBC",
        "SEC",
        "SED",
        "SEI",
        "STA",
        "STX",
        "STY",
        "TAX",
        "TAY",
        "TSX",
        "TXA",
        "TXS",
        "TYA",
        "MIA" 
    };

    void SetFlag(uint8_t flagMask, bool val);

    void ClearFlag(uint8_t flagMask);

    uint8_t GetFlag(uint8_t flagMask);

    void CpuWrite(const uint16_t address, const uint8_t data);

    uint8_t CpuRead(const uint16_t address);

    // This are the diffrent addresing modes:

    uint16_t accum_addr();

    uint16_t imm_addr();

    uint16_t absolute_addr();

    uint16_t zp_addr();

    uint16_t i_zp_x_addr();

    uint16_t i_zp_y_addr();
 
    uint16_t i_absolute_addr_x();

    uint16_t i_absolute_addr_y();

    uint16_t implied_addr();

    uint16_t relative_addr();

    uint16_t i_indirect_addr();

    uint16_t indirect_i_addr();

    uint16_t indirect_addr(); 

    // Instruction set
    void Adc(const Instruction & instruction);
    void And(const Instruction & instruction);
    void Asl(const Instruction & instruction);
    void Bcc(const Instruction & instruction);
    void Bcs(const Instruction & instruction);
    void Beq(const Instruction & instruction);
    void Bit(const Instruction & instruction);
    void Bmi(const Instruction & instruction);
    void Bne(const Instruction & instruction);
    void Bpl(const Instruction & instruction);
    void Brk(const Instruction & instruction);
    void Bvc(const Instruction & instruction);
    void Bvs(const Instruction & instruction);
    void Clc(const Instruction & instruction);
    void Cld(const Instruction & instruction);
    void Cli(const Instruction & instruction);
    void Clv(const Instruction & instruction);
    void Cmp(const Instruction & instruction);
    void Cpx(const Instruction & instruction);
    void Cpy(const Instruction & instruction);
    void Dec(const Instruction & instruction);
    void Dex(const Instruction & instruction);
    void Dey(const Instruction & instruction);
    void Eor(const Instruction & instruction);
    void Inc(const Instruction & instruction);
    void Inx(const Instruction & instruction);
    void Iny(const Instruction & instruction);
    void Jmp(const Instruction & instruction);
    void Jsr(const Instruction & instruction);
    void Lda(const Instruction & instruction);
    void Ldx(const Instruction & instruction);
    void Ldy(const Instruction & instruction);
    void Lsr(const Instruction & instruction);
    void Nop(const Instruction & instruction);
    void Ora(const Instruction & instruction);
    void Pha(const Instruction & instruction);
    void Php(const Instruction & instruction);
    void Pla(const Instruction & instruction);
    void Plp(const Instruction & instruction);
    void Rol(const Instruction & instruction);
    void Ror(const Instruction & instruction);
    void Rti(const Instruction & instruction);
    void Rts(const Instruction & instruction);
    void Sbc(const Instruction & instruction);
    void Sec(const Instruction & instruction);
    void Sed(const Instruction & instruction);
    void Sei(const Instruction & instruction);
    void Sta(const Instruction & instruction);
    void Stx(const Instruction & instruction);
    void Sty(const Instruction & instruction);
    void Tax(const Instruction & instruction);
    void Tay(const Instruction & instruction);
    void Tsx(const Instruction & instruction);
    void Txa(const Instruction & instruction);
    void Txs(const Instruction & instruction);
    void Tya(const Instruction & instruction);
};