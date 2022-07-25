#include <unordered_map>
#include "Mmu.hpp"

class cpu {
private:
    static constexpr uint8_t CARRY_FLAG_MASK = 0x01;
    static constexpr uint8_t ZERO_FLAG_MASK = 0x02;
    static constexpr uint8_t INTERRUPT_DISABLE_FLAG_MASK = 0x04;
    static constexpr uint8_t DECIMAL_MODE_FLAG_MASK = 0x08;
    static constexpr uint8_t BREAK_COMMAND_FLAG_MASK = 0x10;
    static constexpr uint8_t RESERVED_FLAG_MASK = 0x20;
    static constexpr uint8_t OVERFLOW_FLAG_MASK = 0x40;
    static constexpr uint8_t NEGATIVE_FLAG_MASK = 0x80;

    enum class IrqType
    {
        ABORT,
        COP,
        HW_IRQ,
        BRK,
        NMI,
        RESET
    };

    enum class AddrMode
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
        INDIRECT, //The second and third contain a full 16 bit address. From this address you take the effective address is the next 2 bytes.
        LENGTH
    };

    enum class InstructionType
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
        TYA
    };

    struct Instruction 
    {
        InstructionType type;
        uint8_t cycles;
        AddrMode addrMode;
    };

    typedef std::function<uint16_t ()> AddressFunction;
    typedef std::function<void (const Instruction &)> InstructionFunction;

    uint16_t pc; //program counter
    uint8_t sp; //stack
    uint8_t a; //accumulator
    uint8_t x; //index
    uint8_t y; //index
    uint8_t p; //flags
    size_t cycles;
    Mmu mmu; //the mmu
    std::unordered_map<AddrMode, AddressFunction> _address_mode_mapper;
    std::unordered_map<InstructionType, InstructionFunction> _command_type_mapper;
    std::unordered_map<IrqType, std::pair<uint16_t, uint16_t>> _irq_vector_map;

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
    void Cls(const Instruction & instruction);
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
public:

};