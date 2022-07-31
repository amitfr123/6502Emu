#include <stdexcept>

#include "HardwareEmulation/Cartridge.hpp"

Cartridge::Cartridge(std::fstream cartridge_file)
{
    uint8_t mapper_id;
    if (cartridge_file.is_open())
    {
        throw std::runtime_error("Failed to read cartridge_file");
    }
    cartridge_file.read(reinterpret_cast<char*>(&_cartridge_header), sizeof(_cartridge_header));
    _prg_rom_bank_vector.resize(_cartridge_header.prg_rom_bank_count);
    _chr_rom_bank_vector.resize(_cartridge_header.chr_rom_bank_count);
    mapper_id = (_cartridge_header.flags7 & 0xf0) | ((_cartridge_header.flags6 & 0xf0) >> 4);
    if (_cartridge_header.flags6 % 0x4)
    {
        cartridge_file.seekg(512, std::ios_base::cur);
    }
    for (uint32_t i = 0; i < _cartridge_header.prg_rom_bank_count; ++i)
    {
        cartridge_file.read(reinterpret_cast<char*>(_prg_rom_bank_vector[i].data()), _prg_rom_bank_vector[i].size());
    }
    for (uint32_t i = 0; i < _cartridge_header.chr_rom_bank_count; ++i)
    {
        cartridge_file.read(reinterpret_cast<char*>(_chr_rom_bank_vector[i].data()), _chr_rom_bank_vector[i].size());
    }
    cartridge_file.close();
}
