#include "../include/cpu.hpp"

void cpu::SetFlag(uint8_t flagMask, bool val)
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

void cpu::ClearFlag(uint8_t flagMask)
{
    p &= !(flagMask);
}

uint8_t cpu::GetFlag(uint8_t flagMask)
{
    return (p & flagMask)? 1 : 0;
}

void cpu::CpuWrite(const uint16_t address, const uint8_t data)
{
    mmu.MmuWrite(address, data);
}

uint8_t cpu::CpuRead(const uint16_t address)
{
    return mmu.MmuRead(address);
}

uint16_t cpu::accum_addr()
{
    return 0;
}

uint16_t cpu::imm_addr()
{
    return pc++;
}

uint16_t cpu::absolute_addr()
{
    uint16_t lo = CpuRead(pc++);
    uint16_t hi = CpuRead(pc++);
    return lo | (hi << 8);
}

uint16_t cpu::zp_addr()
{
    return CpuRead(pc++);
}

uint16_t cpu::i_zp_x_addr()
{
    return (CpuRead(pc++) + x) & 0x00ff;
}

uint16_t cpu::i_zp_y_addr()
{
    return (CpuRead(pc++) + y) & 0x00ff;
}

uint16_t cpu::i_absolute_addr_x()
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

uint16_t cpu::i_absolute_addr_y()
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

uint16_t cpu::implied_addr()
{
    return 0;
}

uint16_t cpu::relative_addr()
{
    int8_t offset = CpuRead(pc++);
    return pc + offset;
}

uint16_t cpu::i_indirect_addr()
{
    uint16_t zpg_addr = (CpuRead(pc++) + x) & 0x00ff;
    uint16_t addr = 0;
    addr |= CpuRead(zpg_addr++);
    addr |= (CpuRead(zpg_addr) >> 8);
    return addr;
}

uint16_t cpu::indirect_i_addr()
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

uint16_t cpu::indirect_addr()
{
    uint16_t ind_addr = 0;
    uint16_t addr = 0;
    ind_addr |= CpuRead(pc++);
    ind_addr |= CpuRead(pc++) << 8;
    addr |= CpuRead(ind_addr++);
    addr |= (CpuRead(ind_addr) << 8);
    return addr;
}

void cpu::Adc(const Instruction & instruction)
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

void cpu::And(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr);
    a &= data;
    SetFlag(ZERO_FLAG_MASK, !(a));
    SetFlag(NEGATIVE_FLAG_MASK, a & 0x80);
}

void cpu::Asl(const Instruction & instruction)
{
    uint8_t data;
    uint16_t addr;
    if (instruction.addrMode == AddrMode::ACCUM)
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
    if (instruction.addrMode == AddrMode::ACCUM)
    {
        a = temp & 0xff;
    }
    else
    {
        CpuWrite(addr, temp & 0xff);
    }
}

void cpu::Bcc(const Instruction & instruction)
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

void cpu::Bcs(const Instruction & instruction)
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

void cpu::Beq(const Instruction & instruction)
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

void cpu::Bit(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr);
    uint16_t temp = a & data;
    SetFlag(ZERO_FLAG_MASK, !(temp & 0xff));
    SetFlag(OVERFLOW_FLAG_MASK, data & 1 << 6);
    SetFlag(NEGATIVE_FLAG_MASK, data & 1 << 7);
}

void cpu::Bmi(const Instruction & instruction)
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

void cpu::Bne(const Instruction & instruction)
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

void cpu::Bpl(const Instruction & instruction)
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

void cpu::Brk(const Instruction & instruction)
{
    pc++;
    SetFlag(INTERRUPT_DISABLE_FLAG_MASK, true);
    CpuWrite(Mmu::STACK_OFFSET + sp--, (pc >> 8) & 0xff);
    CpuWrite(Mmu::STACK_OFFSET + sp--, pc & 0xff);
    CpuWrite(Mmu::STACK_OFFSET + sp--, p | BREAK_COMMAND_FLAG_MASK);
    pc = CpuRead(_irq_vector_map[IrqType::BRK].first) | (CpuRead(_irq_vector_map[IrqType::BRK].second) << 8);
}

void cpu::Bvc(const Instruction & instruction)
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

void cpu::Bvs(const Instruction & instruction)
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

void cpu::Cls(const Instruction & instruction)
{
    ClearFlag(CARRY_FLAG_MASK);
}

void cpu::Cld(const Instruction & instruction)
{
    ClearFlag(DECIMAL_MODE_FLAG_MASK);
}

void cpu::Cli(const Instruction & instruction)
{
    ClearFlag(INTERRUPT_DISABLE_FLAG_MASK);
}

void cpu::Clv(const Instruction & instruction)
{
    ClearFlag(OVERFLOW_FLAG_MASK);
}

void cpu::Cmp(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr);
    uint16_t temp = a - data;
    SetFlag(CARRY_FLAG_MASK,(a >= data));
    SetFlag(ZERO_FLAG_MASK, !(temp & 0xff));
    SetFlag(NEGATIVE_FLAG_MASK, temp & 0x80);
}

void cpu::Cpx(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr);
    uint16_t temp = x - data;
    SetFlag(CARRY_FLAG_MASK,(x >= data));
    SetFlag(ZERO_FLAG_MASK, !(temp & 0xff));
    SetFlag(NEGATIVE_FLAG_MASK, temp & 0x80);
}

void cpu::Cpy(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr);
    uint16_t temp = y - data;
    SetFlag(CARRY_FLAG_MASK,(y >= data));
    SetFlag(ZERO_FLAG_MASK, !(temp & 0xff));
    SetFlag(NEGATIVE_FLAG_MASK, temp & 0x80);
}

void cpu::Dec(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr) - 1;
    SetFlag(ZERO_FLAG_MASK, !(data));
    SetFlag(NEGATIVE_FLAG_MASK, data & 0x80);
    CpuWrite(addr, data);
}

void cpu::Dex(const Instruction & instruction)
{
    x--;
    SetFlag(ZERO_FLAG_MASK, !(x));
    SetFlag(NEGATIVE_FLAG_MASK, x & 0x80);
}

void cpu::Dey(const Instruction & instruction)
{
    y--;
    SetFlag(ZERO_FLAG_MASK, !(y));
    SetFlag(NEGATIVE_FLAG_MASK, y & 0x80);
}

void cpu::Eor(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr);
    a ^= data;
    SetFlag(ZERO_FLAG_MASK, !(a));
    SetFlag(NEGATIVE_FLAG_MASK, a & 0x80);
}

void cpu::Inc(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr) + 1;
    SetFlag(ZERO_FLAG_MASK, !(data));
    SetFlag(NEGATIVE_FLAG_MASK, data & 0x80);
    CpuWrite(addr, data);
}

void cpu::Inx(const Instruction & instruction)
{
    x++;
    SetFlag(ZERO_FLAG_MASK, !(x));
    SetFlag(NEGATIVE_FLAG_MASK, x & 0x80);
}

void cpu::Iny(const Instruction & instruction)
{
    y++;
    SetFlag(ZERO_FLAG_MASK, !(y));
    SetFlag(NEGATIVE_FLAG_MASK, y & 0x80);
}

void cpu::Jmp(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    pc = addr;
}

void cpu::Jsr(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    CpuWrite(Mmu::STACK_OFFSET + sp--, (pc >> 8) & 0xff);
    CpuWrite(Mmu::STACK_OFFSET + sp--, pc & 0xff);
    pc = addr;
}

void cpu::Lda(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    a = CpuRead(addr);
    SetFlag(ZERO_FLAG_MASK, !(a));
    SetFlag(NEGATIVE_FLAG_MASK, a & 0x80);
}

void cpu::Ldx(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    x = CpuRead(addr);
    SetFlag(ZERO_FLAG_MASK, !(x));
    SetFlag(NEGATIVE_FLAG_MASK, x & 0x80);
}

void cpu::Ldy(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    y = CpuRead(addr);
    SetFlag(ZERO_FLAG_MASK, !(y));
    SetFlag(NEGATIVE_FLAG_MASK, y & 0x80);
}

void cpu::Lsr(const Instruction & instruction)
{
    uint8_t data;
    uint16_t addr;
    if (instruction.addrMode == AddrMode::ACCUM)
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
    if (instruction.addrMode == AddrMode::ACCUM)
    {
        a = temp & 0xff;
    }
    else
    {
        CpuWrite(addr, temp & 0xff);
    }
}

void cpu::Nop(const Instruction & instruction)
{
    // does nothing
}

void cpu::Ora(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    uint8_t data = CpuRead(addr);
    a |= data;
    SetFlag(ZERO_FLAG_MASK, !(a));
    SetFlag(NEGATIVE_FLAG_MASK, a & 0x80);
}

void cpu::Pha(const Instruction & instruction)
{
    CpuWrite(Mmu::STACK_OFFSET + sp--, a);
}

void cpu::Php(const Instruction & instruction)
{
    CpuWrite(Mmu::STACK_OFFSET + sp--, p | BREAK_COMMAND_FLAG_MASK | RESERVED_FLAG_MASK);
}

void cpu::Pla(const Instruction & instruction)
{
    a = CpuRead(Mmu::STACK_OFFSET + ++sp);
    SetFlag(ZERO_FLAG_MASK, !(a));
    SetFlag(NEGATIVE_FLAG_MASK, a & 0x80);
}

void cpu::Plp(const Instruction & instruction)
{
    p = CpuRead(Mmu::STACK_OFFSET + ++sp);
    ClearFlag(BREAK_COMMAND_FLAG_MASK);
    ClearFlag(RESERVED_FLAG_MASK);
}

void cpu::Rol(const Instruction & instruction)
{
    uint8_t data;
    uint16_t addr;
    if (instruction.addrMode == AddrMode::ACCUM)
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
    if (instruction.addrMode == AddrMode::ACCUM)
    {
        a = temp & 0xff;
    }
    else
    {
        CpuWrite(addr, temp & 0xff);
    }
}
void cpu::Ror(const Instruction & instruction)
{
    uint8_t data;
    uint16_t addr;
    if (instruction.addrMode == AddrMode::ACCUM)
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
    if (instruction.addrMode == AddrMode::ACCUM)
    {
        a = temp & 0xff;
    }
    else
    {
        CpuWrite(addr, temp & 0xff);
    }
}

void cpu::Rti(const Instruction & instruction)
{
    p = CpuRead(Mmu::STACK_OFFSET + ++sp);
    pc = CpuRead(Mmu::STACK_OFFSET + ++sp);
    pc |= CpuRead(Mmu::STACK_OFFSET + ++sp) << 8;
    ClearFlag(BREAK_COMMAND_FLAG_MASK);
    ClearFlag(RESERVED_FLAG_MASK);
}

void cpu::Rts(const Instruction & instruction)
{
    pc = CpuRead(Mmu::STACK_OFFSET + ++sp);
    pc |= CpuRead(Mmu::STACK_OFFSET + ++sp) << 8;
    pc++;
}

void cpu::Sbc(const Instruction & instruction)
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

void cpu::Sec(const Instruction & instruction)
{
    SetFlag(CARRY_FLAG_MASK, true);
}

void cpu::Sed(const Instruction & instruction)
{
    SetFlag(DECIMAL_MODE_FLAG_MASK, true);
}

void cpu::Sei(const Instruction & instruction)
{
    SetFlag(INTERRUPT_DISABLE_FLAG_MASK, true);
}

void cpu::Sta(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    CpuWrite(addr, a);
}

void cpu::Stx(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    CpuWrite(addr, x);
}

void cpu::Sty(const Instruction & instruction)
{
    uint16_t addr = _address_mode_mapper[instruction.addrMode]();
    CpuWrite(addr, y);
}

void cpu::Tax(const Instruction & instruction)
{
    x = a;
}

void cpu::Tay(const Instruction & instruction)
{
    y = a;
}

void cpu::Tsx(const Instruction & instruction)
{
    x = sp;
}

void cpu::Txa(const Instruction & instruction)
{
    a = x;
}

void cpu::Txs(const Instruction & instruction)
{
    sp = x;
}

void cpu::Tya(const Instruction & instruction)
{
    a = y;
}