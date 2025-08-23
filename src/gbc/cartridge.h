#ifndef GBC_EMU_CART_H_
#define GBC_EMU_CART_H_
#include "memory.h"
#include <cstdint>

static constexpr unsigned int HEADER_ENTRYPOINT = 0x0100;

class Cartridge {
    public:
        Cartridge();
        ~Cartridge();
        bool load_rom(const char* filepath);
        uint8_t* rom_data;
        unsigned int rom_size;
        unsigned int ram_size;
        uint16_t cart_type;
    private:
        MBC_TYPE eval_cart_type(uint8_t value);
        bool verify_header_checksum();
};
#endif
