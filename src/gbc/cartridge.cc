#include "cartridge.h"
#include "memory.h"
#include <fstream>
#include <iostream>

static constexpr unsigned int CARTRIDGE_TYPE_ADDR = 0x0147;
static constexpr unsigned int ROM_SIZE_ADDR = 0x0148;
static constexpr unsigned int RAM_SIZE_ADDR = 0x0149;
static constexpr unsigned int HEADER_CHECKSUM_ADDR = 0x014D;

Cartridge::Cartridge() {
    rom_data = nullptr;
    rom_size = 0;
    ram_size = 0;
    cart_type = NONE;
}

Cartridge::~Cartridge() {
}

MBC_TYPE Cartridge::eval_cart_type(uint8_t value) {
    return NONE;
}

bool Cartridge::verify_header_checksum() {
    uint8_t checksum = 0;
    for(uint16_t address = 0x0134; address <= 0x014C; address++) {
        checksum = checksum - this->rom_data[address] - 1;
    }

    return this->rom_data[0x014D] == (checksum & 0x00FF);
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
