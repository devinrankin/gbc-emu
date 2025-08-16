#include <iostream>
#include <cstdint>
#include <fstream>
#include "gbc.h"

GBColor::GBColor() {
}
GBColor::~GBColor() {
}

bool GBColor::load_rom(const char* filepath) {
    std::ifstream file(filepath, std::ios::binary);

    file.seekg(0, std::ios::end);
    std::streamsize f_size = file.tellg();
    file.seekg(0, std::ios::beg);

    uint8_t buf[f_size];
    file.read(reinterpret_cast<char*>(buf), f_size);
    cartridge->rom_data = buf;

    return 0;
}
