#include "cartridge.h"
#include <fstream>
#include <iostream>

static constexpr unsigned int CARTRIDGE_TYPE_ADDR = 0x0147;
static constexpr unsigned int ROM_SIZE_ADDR = 0x0148;
static constexpr unsigned int RAM_SIZE_ADDR = 0x0149;
static constexpr unsigned int HEADER_CHECKSUM_ADDR = 0x014D;
static constexpr unsigned int BANK_SIZE = 0x4000;

Cartridge::Cartridge() {
    rom_data = nullptr;
    rom_size = 0;
    ram_size = 0;
    rom_bank0 = nullptr;
    rom_bankX = nullptr;
    curr_bank = 0;
}

Cartridge::~Cartridge() {
}

bool Cartridge::load_rom(const char* filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if(!file) {
        printf("Error reading rom filepath");
        return 1;
    }

    file.seekg(0, std::ios::end);
    std::streamsize f_size = file.tellg();
    file.seekg(0, std::ios::beg);

    uint8_t buf[f_size];
    file.read(reinterpret_cast<char*>(buf), f_size);
    this->rom_data = buf;
    this->rom_size = this->rom_data[ROM_SIZE_ADDR];
    this->cart_type = this->rom_data[CARTRIDGE_TYPE_ADDR];

    return 0;
}

bool Cartridge::verify_header_checksum() {
    uint8_t checksum = 0;
    for(uint16_t address = 0x0134; address <= 0x014C; address++) {
        checksum = checksum - this->rom_data[address] - 1;
    }

    return this->rom_data[0x014D] == (checksum & 0x00FF);
}

uint8_t Cartridge::read_rom(uint16_t address) {
    return this->rom_data[address];
}

void Cartridge::write_rom(uint16_t address, uint8_t value) {
   //TODO: incorporate bank switching when in 0x2000-0x4000 address space
    this->rom_data[address] = value;
}

void Cartridge::switch_bank(uint8_t bank) {
    if(bank == 0) {
        bank = 1;
    }
    rom_bankX = this->rom_data + (bank * BANK_SIZE);
}
