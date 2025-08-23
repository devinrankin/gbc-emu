#ifndef GBC_EMU_CART_H_
#define GBC_EMU_CART_H_
#include <cstddef>
#include <cstdint>

static constexpr unsigned int HEADER_ENTRYPOINT = 0x0100;

class Cartridge {
    public:
        Cartridge();
        ~Cartridge();
        bool load_rom(const char* filepath);
        uint8_t read_rom(uint16_t address);
        void write_rom(uint16_t address, uint8_t value);
    private:
        bool verify_header_checksum();
        void eval_cart_type(uint8_t value);
        void switch_bank(uint8_t bank);
        uint8_t* rom_data;
        size_t rom_size;
        size_t ram_size;
        uint8_t* rom_bank0;
        uint8_t* rom_bankX;
        uint8_t curr_bank;
        uint16_t cart_type;
};
#endif
