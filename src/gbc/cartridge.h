#ifndef GBC_EMU_CART_H_
#define GBC_EMU_CART_H_
#include <cstdint>

class Cartridge {
    public:
        Cartridge();
        ~Cartridge();
        uint8_t* rom_data;
    private:
};
#endif
