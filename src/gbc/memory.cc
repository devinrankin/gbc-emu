#include "memory.h"

Memory::Memory() {
}

uint8_t Memory::read(uint16_t address) {
    if(address < 0x8000) {
        return cartridge->read_rom(address);
    }
    return 0;
}

void Memory::write(uint16_t address, uint8_t value) {
    if(address < 0x8000) {
        cartridge->write_rom(address, value);
    }
}
