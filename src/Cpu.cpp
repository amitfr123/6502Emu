#include "../include/Cpu.hpp"

Cpu::Cpu() : 
    _address_mode_mapper({
        {AMode::ACCUM, std::bind(&Cpu::accum_addr, this)},
        {AMode::IMM, std::bind(&Cpu::imm_addr, this)},
        {AMode::ABSOLUTE, std::bind(&Cpu::absolute_addr, this)},
        {AMode::ZP, std::bind(&Cpu::zp_addr, this)},
        {AMode::I_ZP_X, std::bind(&Cpu::i_zp_x_addr, this)},
        {AMode::I_ZP_Y, std::bind(&Cpu::i_zp_y_addr, this)},
        {AMode::I_ABSOLUTE_X, std::bind(&Cpu::i_absolute_addr_x, this)},
        {AMode::I_ABSOLUTE_Y, std::bind(&Cpu::i_absolute_addr_y, this)},
        {AMode::IMPLIED, std::bind(&Cpu::implied_addr, this)},
        {AMode::RELATIVE, std::bind(&Cpu::relative_addr, this)},
        {AMode::I_INDIRECT, std::bind(&Cpu::i_indirect_addr, this)},
        {AMode::INDIRECT_I, std::bind(&Cpu::indirect_i_addr, this)},
        {AMode::INDIRECT, std::bind(&Cpu::indirect_addr, this)}
    }),
    _instruction_type_mapper({
        {IType::ADC, std::bind(&Cpu::Adc, this, std::placeholders::_1)},
        {IType::AND, std::bind(&Cpu::And, this, std::placeholders::_1)},
        {IType::ASL, std::bind(&Cpu::Asl, this, std::placeholders::_1)},
        {IType::BCC, std::bind(&Cpu::Bcc, this, std::placeholders::_1)},
        {IType::BCS, std::bind(&Cpu::Bcs, this, std::placeholders::_1)},
        {IType::BEQ, std::bind(&Cpu::Beq, this, std::placeholders::_1)},
        {IType::BIT, std::bind(&Cpu::Bit, this, std::placeholders::_1)},
        {IType::BMI, std::bind(&Cpu::Bmi, this, std::placeholders::_1)},
        {IType::BNE, std::bind(&Cpu::Bne, this, std::placeholders::_1)},
        {IType::BPL, std::bind(&Cpu::Bpl, this, std::placeholders::_1)},
        {IType::BRK, std::bind(&Cpu::Brk, this, std::placeholders::_1)},
        {IType::BVC, std::bind(&Cpu::Bvc, this, std::placeholders::_1)},
        {IType::BVS, std::bind(&Cpu::Bvs, this, std::placeholders::_1)},
        {IType::CLC, std::bind(&Cpu::Clc, this, std::placeholders::_1)},
        {IType::CLD, std::bind(&Cpu::Cld, this, std::placeholders::_1)},
        {IType::CLI, std::bind(&Cpu::Cli, this, std::placeholders::_1)},
        {IType::CLV, std::bind(&Cpu::Clv, this, std::placeholders::_1)},
        {IType::CMP, std::bind(&Cpu::Cmp, this, std::placeholders::_1)},
        {IType::CPX, std::bind(&Cpu::Cpx, this, std::placeholders::_1)},
        {IType::CPY, std::bind(&Cpu::Cpy, this, std::placeholders::_1)},
        {IType::DEC, std::bind(&Cpu::Dec, this, std::placeholders::_1)},
        {IType::DEX, std::bind(&Cpu::Dex, this, std::placeholders::_1)},
        {IType::DEY, std::bind(&Cpu::Dey, this, std::placeholders::_1)},
        {IType::EOR, std::bind(&Cpu::Eor, this, std::placeholders::_1)},
        {IType::INC, std::bind(&Cpu::Inc, this, std::placeholders::_1)},
        {IType::INX, std::bind(&Cpu::Inx, this, std::placeholders::_1)},
        {IType::INY, std::bind(&Cpu::Iny, this, std::placeholders::_1)},
        {IType::JMP, std::bind(&Cpu::Jmp, this, std::placeholders::_1)},
        {IType::JSR, std::bind(&Cpu::Jsr, this, std::placeholders::_1)},
        {IType::LDA, std::bind(&Cpu::Lda, this, std::placeholders::_1)},
        {IType::LDX, std::bind(&Cpu::Ldx, this, std::placeholders::_1)},
        {IType::LDY, std::bind(&Cpu::Ldy, this, std::placeholders::_1)},
        {IType::LSR, std::bind(&Cpu::Lsr, this, std::placeholders::_1)},
        {IType::NOP, std::bind(&Cpu::Nop, this, std::placeholders::_1)},
        {IType::ORA, std::bind(&Cpu::Ora, this, std::placeholders::_1)},
        {IType::PHA, std::bind(&Cpu::Pha, this, std::placeholders::_1)},
        {IType::PHP, std::bind(&Cpu::Php, this, std::placeholders::_1)},
        {IType::PLA, std::bind(&Cpu::Pla, this, std::placeholders::_1)},
        {IType::PLP, std::bind(&Cpu::Plp, this, std::placeholders::_1)},
        {IType::ROL, std::bind(&Cpu::Rol, this, std::placeholders::_1)},
        {IType::ROR, std::bind(&Cpu::Ror, this, std::placeholders::_1)},
        {IType::RTI, std::bind(&Cpu::Rti, this, std::placeholders::_1)},
        {IType::RTS, std::bind(&Cpu::Rts, this, std::placeholders::_1)},
        {IType::SBC, std::bind(&Cpu::Sbc, this, std::placeholders::_1)},
        {IType::SEC, std::bind(&Cpu::Sec, this, std::placeholders::_1)},
        {IType::SED, std::bind(&Cpu::Sed, this, std::placeholders::_1)},
        {IType::SEI, std::bind(&Cpu::Sei, this, std::placeholders::_1)},
        {IType::STA, std::bind(&Cpu::Sta, this, std::placeholders::_1)},
        {IType::STX, std::bind(&Cpu::Stx, this, std::placeholders::_1)},
        {IType::STY, std::bind(&Cpu::Sty, this, std::placeholders::_1)},
        {IType::TAX, std::bind(&Cpu::Tax, this, std::placeholders::_1)},
        {IType::TAY, std::bind(&Cpu::Tay, this, std::placeholders::_1)},
        {IType::TSX, std::bind(&Cpu::Tsx, this, std::placeholders::_1)},
        {IType::TXA, std::bind(&Cpu::Txa, this, std::placeholders::_1)},
        {IType::TXS, std::bind(&Cpu::Txs, this, std::placeholders::_1)},
        {IType::TYA, std::bind(&Cpu::Tya, this, std::placeholders::_1)},
        {IType::MIA, std::bind(&Cpu::Nop, this, std::placeholders::_1)}
    }),
    _irq_vector_map({
        {IrqType::ABORT, std::pair<uint32_t,uint32_t>(ABORT_LSB, ABORT_MSB)},
        {IrqType::COP, std::pair<uint32_t,uint32_t>(COP_LSB, COP_MSB)},
        {IrqType::NORMAL_IRQ, std::pair<uint32_t,uint32_t>(NORMAL_IRQ_LSB, NORMAL_IRQ_MSB)},
        {IrqType::BRK, std::pair<uint32_t,uint32_t>(BRK_LSB, BRK_MSB)},
        {IrqType::NMI, std::pair<uint32_t,uint32_t>(NMI_LSB, NMI_MSB)},
        {IrqType::RESET, std::pair<uint32_t,uint32_t>(RESET_LSB, RESET_MSB)},
    }),
    _opcode_vector({
        /*          0                                       1                                   2                                    3                               4                              5                                6                              7                               8                                  9                                       A                              B                                        C                                       D                                      E                                        F
/*0*/   {IType::BRK, AMode::IMPLIED, 7},    {IType::ORA, AMode::I_INDIRECT, 6}, {IType::MIA, AMode::IMPLIED, 2},    {IType::MIA, AMode::I_INDIRECT, 2}, {IType::MIA, AMode::ZP, 3},     {IType::ORA, AMode::ZP, 3},     {IType::ASL, AMode::ZP, 5},     {IType::MIA, AMode::ZP, 5},     {IType::PHP, AMode::IMPLIED, 3}, {IType::ORA, AMode::IMM, 2},           {IType::ASL, AMode::IMPLIED, 2}, {IType::MIA, AMode::IMM, 2},           {IType::MIA, AMode::ABSOLUTE, 4},       {IType::ORA, AMode::ABSOLUTE, 4},       {IType::ASL, AMode::ABSOLUTE, 6},       {IType::MIA, AMode::ABSOLUTE, 6},
/*1*/   {IType::BPL, AMode::RELATIVE, 2},   {IType::ORA, AMode::INDIRECT_I, 5}, {IType::MIA, AMode::IMPLIED, 2},    {IType::MIA, AMode::INDIRECT_I, 8}, {IType::MIA, AMode::I_ZP_X, 4}, {IType::ORA, AMode::I_ZP_X, 4}, {IType::ASL, AMode::I_ZP_X, 6}, {IType::MIA, AMode::I_ZP_X, 6}, {IType::CLC, AMode::IMPLIED, 2}, {IType::ORA, AMode::I_ABSOLUTE_Y, 4},  {IType::MIA, AMode::IMPLIED, 2}, {IType::MIA, AMode::I_ABSOLUTE_Y, 7},  {IType::MIA, AMode::I_ABSOLUTE_X, 4},   {IType::ORA, AMode::I_ABSOLUTE_X, 4},   {IType::ASL, AMode::I_ABSOLUTE_X, 7},   {IType::MIA, AMode::I_ABSOLUTE_X, 7},
/*2*/   {IType::JSR, AMode::ABSOLUTE, 6},   {IType::AND, AMode::I_INDIRECT, 6}, {IType::MIA, AMode::IMPLIED, 2},    {IType::MIA, AMode::I_INDIRECT, 8}, {IType::BIT, AMode::ZP, 3},     {IType::AND, AMode::ZP, 3},     {IType::ROL, AMode::ZP, 5},     {IType::MIA, AMode::ZP, 5},     {IType::PLP, AMode::IMPLIED, 4}, {IType::AND, AMode::IMM, 2},           {IType::ROL, AMode::IMPLIED, 2}, {IType::MIA, AMode::IMM, 2},           {IType::BIT, AMode::ABSOLUTE, 4},       {IType::AND, AMode::ABSOLUTE, 4},       {IType::ROL, AMode::ABSOLUTE, 6},       {IType::MIA, AMode::ABSOLUTE, 6},
/*3*/   {IType::BMI, AMode::RELATIVE, 2},   {IType::AND, AMode::INDIRECT_I, 5}, {IType::MIA, AMode::IMPLIED, 2},    {IType::MIA, AMode::I_INDIRECT, 8}, {IType::MIA, AMode::I_ZP_X, 4}, {IType::AND, AMode::I_ZP_X, 4}, {IType::ROL, AMode::I_ZP_X, 6}, {IType::MIA, AMode::I_ZP_X, 6}, {IType::SEC, AMode::IMPLIED, 2}, {IType::AND, AMode::I_ABSOLUTE_Y, 4},  {IType::MIA, AMode::IMPLIED, 2}, {IType::MIA, AMode::I_ABSOLUTE_Y, 7},  {IType::MIA, AMode::I_ABSOLUTE_X, 4},   {IType::AND, AMode::I_ABSOLUTE_X, 4},   {IType::ROL, AMode::I_ABSOLUTE_X, 7},   {IType::MIA, AMode::I_ABSOLUTE_X, 7},
/*4*/   {IType::RTI, AMode::IMPLIED, 6},    {IType::EOR, AMode::I_INDIRECT, 6}, {IType::MIA, AMode::IMPLIED, 2},    {IType::MIA, AMode::I_INDIRECT, 8}, {IType::MIA, AMode::ZP, 3},     {IType::EOR, AMode::ZP, 3},     {IType::LSR, AMode::ZP, 5},     {IType::MIA, AMode::ZP, 5},     {IType::PHA, AMode::IMPLIED, 3}, {IType::EOR, AMode::IMM, 2},           {IType::LSR, AMode::IMPLIED, 2}, {IType::MIA, AMode::IMM, 2},           {IType::JMP, AMode::ABSOLUTE, 3},       {IType::EOR, AMode::ABSOLUTE, 4},       {IType::LSR, AMode::ABSOLUTE, 6},       {IType::MIA, AMode::ABSOLUTE, 6},
/*5*/   {IType::BVC, AMode::RELATIVE, 2},   {IType::EOR, AMode::INDIRECT_I, 5}, {IType::MIA, AMode::IMPLIED, 2},    {IType::MIA, AMode::INDIRECT_I, 8}, {IType::MIA, AMode::I_ZP_X, 4}, {IType::EOR, AMode::I_ZP_X, 4}, {IType::LSR, AMode::I_ZP_X, 6}, {IType::MIA, AMode::I_ZP_X, 6}, {IType::CLI, AMode::IMPLIED, 2}, {IType::EOR, AMode::I_ABSOLUTE_Y, 4},  {IType::MIA, AMode::IMPLIED, 2}, {IType::MIA, AMode::I_ABSOLUTE_Y, 7},  {IType::MIA, AMode::I_ABSOLUTE_X, 4},   {IType::EOR, AMode::I_ABSOLUTE_X, 4},   {IType::LSR, AMode::I_ABSOLUTE_X, 7},   {IType::MIA, AMode::I_ABSOLUTE_X, 7},
/*6*/   {IType::RTS, AMode::IMPLIED, 6},    {IType::ADC, AMode::INDIRECT_I, 6}, {IType::MIA, AMode::IMPLIED, 2},    {IType::MIA, AMode::I_INDIRECT, 8}, {IType::MIA, AMode::ZP, 3},     {IType::ADC, AMode::ZP, 3},     {IType::ROR, AMode::ZP, 5},     {IType::MIA, AMode::ZP, 5},     {IType::PLA, AMode::IMPLIED, 4}, {IType::ADC, AMode::IMM, 2},           {IType::ROR, AMode::IMPLIED, 2}, {IType::MIA, AMode::IMM, 2},           {IType::JMP, AMode::INDIRECT, 5},       {IType::ADC, AMode::ABSOLUTE, 4},       {IType::ROR, AMode::ABSOLUTE, 6},       {IType::MIA, AMode::ABSOLUTE, 6},
/*7*/   {IType::BVS, AMode::RELATIVE, 2},   {IType::ADC, AMode::INDIRECT_I, 5}, {IType::MIA, AMode::IMPLIED, 2},    {IType::MIA, AMode::INDIRECT_I, 8}, {IType::MIA, AMode::I_ZP_X, 4}, {IType::ADC, AMode::I_ZP_X, 4}, {IType::ROR, AMode::I_ZP_X, 6}, {IType::MIA, AMode::I_ZP_X, 6}, {IType::SEI, AMode::IMPLIED, 2}, {IType::ADC, AMode::I_ABSOLUTE_Y, 4},  {IType::MIA, AMode::IMPLIED, 2}, {IType::MIA, AMode::I_ABSOLUTE_Y, 7},  {IType::MIA, AMode::I_ABSOLUTE_X, 4},   {IType::ADC, AMode::I_ABSOLUTE_X, 4},   {IType::ROR, AMode::I_ABSOLUTE_X, 7},   {IType::MIA, AMode::I_ABSOLUTE_X, 7},
/*8*/   {IType::MIA, AMode::IMM, 2},        {IType::STA, AMode::I_INDIRECT, 6}, {IType::MIA, AMode::IMM, 2},        {IType::MIA, AMode::I_INDIRECT, 6}, {IType::STY, AMode::ZP, 3},     {IType::STA, AMode::ZP, 3},     {IType::STX, AMode::ZP, 3},     {IType::MIA, AMode::ZP, 3},     {IType::DEY, AMode::IMPLIED, 2}, {IType::MIA, AMode::IMM, 2},           {IType::TXA, AMode::IMPLIED, 2}, {IType::MIA, AMode::IMM, 2},           {IType::STY, AMode::ABSOLUTE, 4},       {IType::STA, AMode::ABSOLUTE, 4},       {IType::STX, AMode::ABSOLUTE, 4},       {IType::MIA, AMode::ABSOLUTE, 4},
/*9*/   {IType::BCC, AMode::RELATIVE, 2},   {IType::STA, AMode::INDIRECT_I, 6}, {IType::MIA, AMode::IMPLIED, 2},    {IType::MIA, AMode::INDIRECT_I, 6}, {IType::STY, AMode::I_ZP_X, 4}, {IType::STA, AMode::I_ZP_X, 4}, {IType::STX, AMode::I_ZP_Y, 4}, {IType::MIA, AMode::I_ZP_Y, 4}, {IType::TYA, AMode::IMPLIED, 2}, {IType::STA, AMode::I_ABSOLUTE_Y, 5},  {IType::TXS, AMode::IMPLIED, 2}, {IType::MIA, AMode::I_ABSOLUTE_Y, 5},  {IType::MIA, AMode::I_ABSOLUTE_X, 5},   {IType::STX, AMode::I_ABSOLUTE_X, 5},   {IType::MIA, AMode::I_ABSOLUTE_Y, 5},   {IType::MIA, AMode::I_ABSOLUTE_Y, 5},
/*A*/   {IType::LDY, AMode::IMM, 2},        {IType::LDA, AMode::I_INDIRECT, 6}, {IType::LDX, AMode::IMM, 2},        {IType::MIA, AMode::I_INDIRECT, 6}, {IType::LDY, AMode::ZP, 3},     {IType::LDA, AMode::ZP, 3},     {IType::LDX, AMode::ZP, 3},     {IType::MIA, AMode::ZP, 3},     {IType::TAY, AMode::IMPLIED, 2}, {IType::LDA, AMode::IMM, 2},           {IType::TAX, AMode::IMPLIED, 2}, {IType::MIA, AMode::IMM, 2},           {IType::LDY, AMode::ABSOLUTE, 4},       {IType::LDA, AMode::ABSOLUTE, 4},       {IType::LDX, AMode::ABSOLUTE, 4},       {IType::MIA, AMode::ABSOLUTE, 4},
/*B*/   {IType::BCS, AMode::RELATIVE, 2},   {IType::LDA, AMode::INDIRECT_I, 5}, {IType::MIA, AMode::IMPLIED, 2},    {IType::MIA, AMode::INDIRECT_I, 5}, {IType::LDY, AMode::I_ZP_X, 4}, {IType::LDA, AMode::I_ZP_X, 4}, {IType::LDX, AMode::I_ZP_Y, 4}, {IType::MIA, AMode::I_ZP_Y, 4}, {IType::CLV, AMode::IMPLIED, 2}, {IType::LDA, AMode::I_ABSOLUTE_Y, 4},  {IType::TSX, AMode::IMPLIED, 2}, {IType::MIA, AMode::I_ABSOLUTE_Y, 4},  {IType::LDY, AMode::I_ABSOLUTE_X, 4},   {IType::LDA, AMode::I_ABSOLUTE_X, 4},   {IType::LDX, AMode::I_ABSOLUTE_Y, 4},   {IType::MIA, AMode::I_ABSOLUTE_Y, 4},
/*C*/   {IType::CPY, AMode::IMM, 2},        {IType::CMP, AMode::I_INDIRECT, 6}, {IType::MIA, AMode::IMM, 2},        {IType::MIA, AMode::I_INDIRECT, 8}, {IType::CPY, AMode::ZP, 3},     {IType::CMP, AMode::ZP, 3},     {IType::DEC, AMode::ZP, 5},     {IType::MIA, AMode::ZP, 5},     {IType::INY, AMode::IMPLIED, 2}, {IType::CMP, AMode::IMM, 2},           {IType::DEX, AMode::IMPLIED, 2}, {IType::MIA, AMode::IMM, 2},           {IType::CPY, AMode::ABSOLUTE, 4},       {IType::CMP, AMode::ABSOLUTE, 4},       {IType::DEC, AMode::ABSOLUTE, 6},       {IType::MIA, AMode::ABSOLUTE, 6},
/*D*/   {IType::BNE, AMode::RELATIVE, 2},   {IType::CMP, AMode::INDIRECT_I, 5}, {IType::MIA, AMode::IMPLIED, 2},    {IType::MIA, AMode::INDIRECT_I, 8}, {IType::MIA, AMode::I_ZP_X, 4}, {IType::CMP, AMode::I_ZP_X, 4}, {IType::DEC, AMode::I_ZP_X, 6}, {IType::MIA, AMode::I_ZP_X, 6}, {IType::CLD, AMode::IMPLIED, 2}, {IType::CMP, AMode::I_ABSOLUTE_Y, 4},  {IType::MIA, AMode::IMPLIED, 2}, {IType::MIA, AMode::I_ABSOLUTE_Y, 7},  {IType::MIA, AMode::I_ABSOLUTE_X, 4},   {IType::CMP, AMode::I_ABSOLUTE_X, 4},   {IType::DEC, AMode::I_ABSOLUTE_X, 7},   {IType::MIA, AMode::I_ABSOLUTE_X, 7},
/*E*/   {IType::CPX, AMode::IMM, 2},        {IType::SBC, AMode::I_INDIRECT, 6}, {IType::MIA, AMode::IMM, 2},        {IType::MIA, AMode::I_INDIRECT, 8}, {IType::CPX, AMode::ZP, 3},     {IType::SBC, AMode::ZP, 3},     {IType::INC, AMode::ZP, 5},     {IType::MIA, AMode::ZP, 5},     {IType::INX, AMode::IMPLIED, 2}, {IType::SBC, AMode::IMM, 2},           {IType::NOP, AMode::IMPLIED, 2}, {IType::MIA, AMode::IMM, 2},           {IType::CPX, AMode::ABSOLUTE, 4},       {IType::SBC, AMode::ABSOLUTE, 4},       {IType::INC, AMode::ABSOLUTE, 6},       {IType::MIA, AMode::ABSOLUTE, 6},
/*F*/   {IType::BEQ, AMode::RELATIVE, 2},   {IType::SBC, AMode::INDIRECT_I, 6}, {IType::MIA, AMode::IMPLIED, 2},    {IType::MIA, AMode::INDIRECT_I, 8}, {IType::MIA, AMode::I_ZP_X, 4}, {IType::SBC, AMode::I_ZP_X, 4}, {IType::INC, AMode::I_ZP_X, 6}, {IType::MIA, AMode::I_ZP_X, 6}, {IType::SED, AMode::IMPLIED, 2}, {IType::SBC, AMode::I_ABSOLUTE_Y, 4},  {IType::MIA, AMode::IMPLIED, 2}, {IType::MIA, AMode::I_ABSOLUTE_Y, 7},  {IType::MIA, AMode::I_ABSOLUTE_X, 4},   {IType::SBC, AMode::I_ABSOLUTE_X, 4},   {IType::INC, AMode::I_ABSOLUTE_X, 7},   {IType::MIA, AMode::I_ABSOLUTE_X, 7}
    })
{
}

void Cpu::SetFlag(uint8_t flagMask, bool val)
{
    if (val)
    {
        p |= flagMask;
    }
    else
    {
        ClearFlag(flagMask);
    }
}

void Cpu::ClearFlag(uint8_t flagMask)
{
    p &= !(flagMask);
}

uint8_t Cpu::GetFlag(uint8_t flagMask)
{
    return (p & flagMask)? 1 : 0;
}

void Cpu::CpuWrite(const uint16_t address, const uint8_t data)
{
    mmu.MmuWrite(address, data);
}

uint8_t Cpu::CpuRead(const uint16_t address)
{
    return mmu.MmuRead(address);
}

uint16_t Cpu::accum_addr()
{
    return 0;
}

uint16_t Cpu::imm_addr()
{
    return pc++;
}

uint16_t Cpu::absolute_addr()
{
    uint16_t lo = CpuRead(pc++);
    uint16_t hi = CpuRead(pc++);
    return lo | (hi << 8);
}

uint16_t Cpu::zp_addr()
{
    return CpuRead(pc++);
}

uint16_t Cpu::i_zp_x_addr()
{
    return (CpuRead(pc++) + x) & 0x00ff;
}

uint16_t Cpu::i_zp_y_addr()
{
    return (CpuRead(pc++) + y) & 0x00ff;
}

uint16_t Cpu::i_absolute_addr_x()
{
    uint16_t lo = CpuRead(pc++);
    uint16_t hi = CpuRead(pc++);
    uint16_t addr = 0;
    addr = (lo | (hi << 8)) + x;
    if ((addr & 0xff00) != hi)
    {
        cycles++;
    }
    return addr;
}

uint16_t Cpu::i_absolute_addr_y()
{
    uint16_t lo = CpuRead(pc++);
    uint16_t hi = CpuRead(pc++);
    uint16_t addr = 0;
    addr = (lo | (hi << 8)) + y;
    if ((addr & 0xff00) != hi)
    {
        cycles++;
    }
    return addr;
}

uint16_t Cpu::implied_addr()
{
    return 0;
}

uint16_t Cpu::relative_addr()
{
    int8_t offset = CpuRead(pc++);
    return pc + offset;
}

uint16_t Cpu::i_indirect_addr()
{
    uint16_t zpg_addr = (CpuRead(pc++) + x) & 0x00ff;
    uint16_t addr = 0;
    addr |= CpuRead(zpg_addr++);
    addr |= (CpuRead(zpg_addr) >> 8);
    return addr;
}

uint16_t Cpu::indirect_i_addr()
{
    uint16_t zpg_addr = CpuRead(pc++);
    uint16_t addr = 0;
    addr |= CpuRead(zpg_addr++);
    addr |= (CpuRead(zpg_addr) << 8);
    if ((addr + y) & 0xff00 != addr & 0xff00)
    {
        cycles++;
    }
    return addr + y;
}

uint16_t Cpu::indirect_addr()
{
    uint16_t ind_addr = 0;
    uint16_t addr = 0;
    ind_addr |= CpuRead(pc++);
    ind_addr |= CpuRead(pc++) << 8;
    addr |= CpuRead(ind_addr++);
    addr |= (CpuRead(ind_addr) << 8);
    return addr;
}

void Cpu::Adc(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr);
    uint16_t temp = GetFlag(CARRY_FLAG_MASK) + data + a;
    SetFlag(CARRY_FLAG_MASK, temp & 0xff00);
    SetFlag(ZERO_FLAG_MASK, !(temp & 0xff));
    SetFlag(OVERFLOW_FLAG_MASK, (a ^ temp) & (data ^ temp) & 0x80);
    SetFlag(NEGATIVE_FLAG_MASK, temp & 0x80);
    a = temp & 0xff;
}

void Cpu::And(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr);
    a &= data;
    SetFlag(ZERO_FLAG_MASK, !(a));
    SetFlag(NEGATIVE_FLAG_MASK, a & 0x80);
}

void Cpu::Asl(const Instruction & instruction)
{
    uint8_t data;
    uint16_t addr;
    if (instruction.addrMode == AMode::ACCUM)
    {
        data = a;
    }
    else
    {
        addr = _address_mode_mapper[instruction.addrMode]();
        data = CpuRead(addr);
    }
    uint16_t temp = data << 1;
    SetFlag(CARRY_FLAG_MASK, temp & 0xff00);
    SetFlag(ZERO_FLAG_MASK, !(temp & 0xff));
    SetFlag(NEGATIVE_FLAG_MASK, temp & 0x80);
    if (instruction.addrMode == AMode::ACCUM)
    {
        a = temp & 0xff;
    }
    else
    {
        CpuWrite(addr, temp & 0xff);
    }
}

void Cpu::Bcc(const Instruction & instruction)
{
    if (!GetFlag(CARRY_FLAG_MASK))
    {
        uint16_t addr = _address_mode_mapper[instruction.addrMode]();
        uint16_t temp = CpuRead(addr) + pc;
        if (temp & 0xff != pc % 0xff)
        {
            cycles++;
        }
        pc = temp;
    }
}

void Cpu::Bcs(const Instruction & instruction)
{
    if (GetFlag(CARRY_FLAG_MASK))
    {
        uint16_t addr = _address_mode_mapper[instruction.addrMode]();
        uint16_t temp = CpuRead(addr) + pc;
        if (temp & 0xff != pc % 0xff)
        {
            cycles++;
        }
        pc = temp;
    }
}

void Cpu::Beq(const Instruction & instruction)
{
    if (GetFlag(ZERO_FLAG_MASK))
    {
        uint16_t addr = _address_mode_mapper[instruction.addrMode]();
        uint16_t temp = CpuRead(addr) + pc;
        if (temp & 0xff != pc % 0xff)
        {
            cycles++;
        }
        pc = temp;
    }
}

void Cpu::Bit(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr);
    uint16_t temp = a & data;
    SetFlag(ZERO_FLAG_MASK, !(temp & 0xff));
    SetFlag(OVERFLOW_FLAG_MASK, data & 1 << 6);
    SetFlag(NEGATIVE_FLAG_MASK, data & 1 << 7);
}

void Cpu::Bmi(const Instruction & instruction)
{
    if (GetFlag(NEGATIVE_FLAG_MASK))
    {
        uint16_t addr = _address_mode_mapper[instruction.addrMode]();
        uint16_t temp = CpuRead(addr) + pc;
        if (temp & 0xff != pc % 0xff)
        {
            cycles++;
        }
        pc = temp;
    }
}

void Cpu::Bne(const Instruction & instruction)
{
    if (!GetFlag(ZERO_FLAG_MASK))
    {
        uint16_t addr = _address_mode_mapper[instruction.addrMode]();
        uint16_t temp = CpuRead(addr) + pc;
        if (temp & 0xff != pc % 0xff)
        {
            cycles++;
        }
        pc = temp;
    }
}

void Cpu::Bpl(const Instruction & instruction)
{
    if (!GetFlag(NEGATIVE_FLAG_MASK))
    {
        uint16_t addr = _address_mode_mapper[instruction.addrMode]();
        uint16_t temp = CpuRead(addr) + pc;
        if (temp & 0xff != pc % 0xff)
        {
            cycles++;
        }
        pc = temp;
    }
}

void Cpu::Brk(const Instruction & instruction)
{
    pc++;
    SetFlag(INTERRUPT_DISABLE_FLAG_MASK, true);
    CpuWrite(Mmu::STACK_OFFSET + sp--, (pc >> 8) & 0xff);
    CpuWrite(Mmu::STACK_OFFSET + sp--, pc & 0xff);
    CpuWrite(Mmu::STACK_OFFSET + sp--, p | BREAK_COMMAND_FLAG_MASK);
    pc = CpuRead(_irq_vector_map[IrqType::BRK].first) | (CpuRead(_irq_vector_map[IrqType::BRK].second) << 8);
}

void Cpu::Bvc(const Instruction & instruction)
{
    if (!GetFlag(OVERFLOW_FLAG_MASK))
    {
        uint16_t addr = _address_mode_mapper[instruction.addrMode]();
        uint16_t temp = CpuRead(addr) + pc;
        if (temp & 0xff != pc % 0xff)
        {
            cycles++;
        }
        pc = temp;
    }
}

void Cpu::Bvs(const Instruction & instruction)
{
    if (GetFlag(OVERFLOW_FLAG_MASK))
    {
        uint16_t addr = _address_mode_mapper[instruction.addrMode]();
        uint16_t temp = CpuRead(addr) + pc;
        if (temp & 0xff != pc % 0xff)
        {
            cycles++;
        }
        pc = temp;
    }
}

void Cpu::Clc(const Instruction & instruction)
{
    ClearFlag(CARRY_FLAG_MASK);
}

void Cpu::Cld(const Instruction & instruction)
{
    ClearFlag(DECIMAL_MODE_FLAG_MASK);
}

void Cpu::Cli(const Instruction & instruction)
{
    ClearFlag(INTERRUPT_DISABLE_FLAG_MASK);
}

void Cpu::Clv(const Instruction & instruction)
{
    ClearFlag(OVERFLOW_FLAG_MASK);
}

void Cpu::Cmp(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr);
    uint16_t temp = a - data;
    SetFlag(CARRY_FLAG_MASK,(a >= data));
    SetFlag(ZERO_FLAG_MASK, !(temp & 0xff));
    SetFlag(NEGATIVE_FLAG_MASK, temp & 0x80);
}

void Cpu::Cpx(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr);
    uint16_t temp = x - data;
    SetFlag(CARRY_FLAG_MASK,(x >= data));
    SetFlag(ZERO_FLAG_MASK, !(temp & 0xff));
    SetFlag(NEGATIVE_FLAG_MASK, temp & 0x80);
}

void Cpu::Cpy(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr);
    uint16_t temp = y - data;
    SetFlag(CARRY_FLAG_MASK,(y >= data));
    SetFlag(ZERO_FLAG_MASK, !(temp & 0xff));
    SetFlag(NEGATIVE_FLAG_MASK, temp & 0x80);
}

void Cpu::Dec(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr) - 1;
    SetFlag(ZERO_FLAG_MASK, !(data));
    SetFlag(NEGATIVE_FLAG_MASK, data & 0x80);
    CpuWrite(addr, data);
}

void Cpu::Dex(const Instruction & instruction)
{
    x--;
    SetFlag(ZERO_FLAG_MASK, !(x));
    SetFlag(NEGATIVE_FLAG_MASK, x & 0x80);
}

void Cpu::Dey(const Instruction & instruction)
{
    y--;
    SetFlag(ZERO_FLAG_MASK, !(y));
    SetFlag(NEGATIVE_FLAG_MASK, y & 0x80);
}

void Cpu::Eor(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr);
    a ^= data;
    SetFlag(ZERO_FLAG_MASK, !(a));
    SetFlag(NEGATIVE_FLAG_MASK, a & 0x80);
}

void Cpu::Inc(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr) + 1;
    SetFlag(ZERO_FLAG_MASK, !(data));
    SetFlag(NEGATIVE_FLAG_MASK, data & 0x80);
    CpuWrite(addr, data);
}

void Cpu::Inx(const Instruction & instruction)
{
    x++;
    SetFlag(ZERO_FLAG_MASK, !(x));
    SetFlag(NEGATIVE_FLAG_MASK, x & 0x80);
}

void Cpu::Iny(const Instruction & instruction)
{
    y++;
    SetFlag(ZERO_FLAG_MASK, !(y));
    SetFlag(NEGATIVE_FLAG_MASK, y & 0x80);
}

void Cpu::Jmp(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    pc = addr;
}

void Cpu::Jsr(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    CpuWrite(Mmu::STACK_OFFSET + sp--, (pc >> 8) & 0xff);
    CpuWrite(Mmu::STACK_OFFSET + sp--, pc & 0xff);
    pc = addr;
}

void Cpu::Lda(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    a = CpuRead(addr);
    SetFlag(ZERO_FLAG_MASK, !(a));
    SetFlag(NEGATIVE_FLAG_MASK, a & 0x80);
}

void Cpu::Ldx(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    x = CpuRead(addr);
    SetFlag(ZERO_FLAG_MASK, !(x));
    SetFlag(NEGATIVE_FLAG_MASK, x & 0x80);
}

void Cpu::Ldy(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    y = CpuRead(addr);
    SetFlag(ZERO_FLAG_MASK, !(y));
    SetFlag(NEGATIVE_FLAG_MASK, y & 0x80);
}

void Cpu::Lsr(const Instruction & instruction)
{
    uint8_t data;
    uint16_t addr;
    if (instruction.addrMode == AMode::ACCUM)
    {
        data = a;
    }
    else
    {
        addr = _address_mode_mapper[instruction.addrMode]();
        data = CpuRead(addr);
    }
    uint16_t temp = data >> 1;
    SetFlag(CARRY_FLAG_MASK, data & 0x1);
    SetFlag(ZERO_FLAG_MASK, !(temp & 0xff));
    ClearFlag(NEGATIVE_FLAG_MASK);
    if (instruction.addrMode == AMode::ACCUM)
    {
        a = temp & 0xff;
    }
    else
    {
        CpuWrite(addr, temp & 0xff);
    }
}

void Cpu::Nop(const Instruction & instruction)
{
    // does nothing
}

void Cpu::Ora(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr);
    a |= data;
    SetFlag(ZERO_FLAG_MASK, !(a));
    SetFlag(NEGATIVE_FLAG_MASK, a & 0x80);
}

void Cpu::Pha(const Instruction & instruction)
{
    CpuWrite(Mmu::STACK_OFFSET + sp--, a);
}

void Cpu::Php(const Instruction & instruction)
{
    CpuWrite(Mmu::STACK_OFFSET + sp--, p | BREAK_COMMAND_FLAG_MASK | RESERVED_FLAG_MASK);
}

void Cpu::Pla(const Instruction & instruction)
{
    a = CpuRead(Mmu::STACK_OFFSET + ++sp);
    SetFlag(ZERO_FLAG_MASK, !(a));
    SetFlag(NEGATIVE_FLAG_MASK, a & 0x80);
}

void Cpu::Plp(const Instruction & instruction)
{
    p = CpuRead(Mmu::STACK_OFFSET + ++sp);
    ClearFlag(BREAK_COMMAND_FLAG_MASK);
    ClearFlag(RESERVED_FLAG_MASK);
}

void Cpu::Rol(const Instruction & instruction)
{
    uint8_t data;
    uint16_t addr;
    if (instruction.addrMode == AMode::ACCUM)
    {
        data = a;
    }
    else
    {
        addr = _address_mode_mapper[instruction.addrMode]();
        data = CpuRead(addr);
    }
    uint16_t temp = data << 1;
    temp |= (data & 0x80) >> 7;
    SetFlag(CARRY_FLAG_MASK, temp & 0xff00);
    SetFlag(ZERO_FLAG_MASK, !(temp & 0xff));
    SetFlag(NEGATIVE_FLAG_MASK, temp & 0x80);
    if (instruction.addrMode == AMode::ACCUM)
    {
        a = temp & 0xff;
    }
    else
    {
        CpuWrite(addr, temp & 0xff);
    }
}
void Cpu::Ror(const Instruction & instruction)
{
    uint8_t data;
    uint16_t addr;
    if (instruction.addrMode == AMode::ACCUM)
    {
        data = a;
    }
    else
    {
        addr = _address_mode_mapper[instruction.addrMode]();
        data = CpuRead(addr);
    }
    uint16_t temp = data >> 1;
    temp |= (data & 0x1) << 7;
    SetFlag(CARRY_FLAG_MASK, data & 0x1);
    SetFlag(ZERO_FLAG_MASK, !(temp & 0xff));
    SetFlag(NEGATIVE_FLAG_MASK, temp & 0x80);
    if (instruction.addrMode == AMode::ACCUM)
    {
        a = temp & 0xff;
    }
    else
    {
        CpuWrite(addr, temp & 0xff);
    }
}

void Cpu::Rti(const Instruction & instruction)
{
    p = CpuRead(Mmu::STACK_OFFSET + ++sp);
    pc = CpuRead(Mmu::STACK_OFFSET + ++sp);
    pc |= CpuRead(Mmu::STACK_OFFSET + ++sp) << 8;
    ClearFlag(BREAK_COMMAND_FLAG_MASK);
    ClearFlag(RESERVED_FLAG_MASK);
}

void Cpu::Rts(const Instruction & instruction)
{
    pc = CpuRead(Mmu::STACK_OFFSET + ++sp);
    pc |= CpuRead(Mmu::STACK_OFFSET + ++sp) << 8;
    pc++;
}

void Cpu::Sbc(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr);
    uint16_t temp = a - data - GetFlag(CARRY_FLAG_MASK);
    SetFlag(CARRY_FLAG_MASK, temp & 0xff00);
    SetFlag(ZERO_FLAG_MASK, !(temp & 0xff));
    SetFlag(OVERFLOW_FLAG_MASK, (a ^ temp) & (data ^ temp) & 0x80);
    SetFlag(NEGATIVE_FLAG_MASK, temp & 0x80);
    a = temp & 0xff;
}

void Cpu::Sec(const Instruction & instruction)
{
    SetFlag(CARRY_FLAG_MASK, true);
}

void Cpu::Sed(const Instruction & instruction)
{
    SetFlag(DECIMAL_MODE_FLAG_MASK, true);
}

void Cpu::Sei(const Instruction & instruction)
{
    SetFlag(INTERRUPT_DISABLE_FLAG_MASK, true);
}

void Cpu::Sta(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    CpuWrite(addr, a);
}

void Cpu::Stx(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    CpuWrite(addr, x);
}

void Cpu::Sty(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    CpuWrite(addr, y);
}

void Cpu::Tax(const Instruction & instruction)
{
    x = a;
}

void Cpu::Tay(const Instruction & instruction)
{
    y = a;
}

void Cpu::Tsx(const Instruction & instruction)
{
    x = sp;
}

void Cpu::Txa(const Instruction & instruction)
{
    a = x;
}

void Cpu::Txs(const Instruction & instruction)
{
    sp = x;
}

void Cpu::Tya(const Instruction & instruction)
{
    a = y;
}