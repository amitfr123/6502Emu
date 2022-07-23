#include <array>
#include <vector>
#include <functional>

#include <stdint.h>

class Mmu {
private:
    static constexpr uint32_t TRUE_RAM_SIZE = 0x800;
    static constexpr uint32_t RAM_MEMORY_RANGE = 0x2000;

    typedef std::function<void (const uint16_t address, const uint8_t data)> WriteFunction;
    typedef std::function<uint8_t (const uint16_t address)> ReadFunction;

    struct phis_transltion
    {
        WriteFunction writeFunc;
        ReadFunction readFunc;
        uint32_t offset;
        uint32_t size;
    };
    std::vector<phis_transltion> _memoryMapper;
    std::array<uint8_t, 0x800> _ram;

    void RamWrite(const uint16_t address, const uint8_t data);

    uint8_t RamRead(const uint16_t address);
public:
    static constexpr uint32_t STACK_OFFSET = 0x100;
    static constexpr uint32_t STACK_SIZE = 0x100;

    void MmuWrite(const uint16_t address, const uint8_t data);

    uint8_t MmuRead(const uint16_t address);
};