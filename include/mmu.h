#ifndef MMU
#define MMU

#include <stdint.h>

#define TRUE_RAM_SIZE 0x800
#define RAM_RANGE 0x2000

typedef struct
{
    uint8_t * ram;
}mmu_t;

int mmu_init(mmu_t * mmu);

// data is uint 8 because thats the data bus size
void mmu_write(const mmu_t mmu, const uint16_t address, uint8_t data);

uint8_t mmu_read(const mmu_t mmu, const uint16_t address);

#endif // MMU