#ifndef GBC_EMU_CART_H_
#define GBC_EMU_CART_H_
#include <array>
#include <cstddef>
#include <cstdint>

static constexpr unsigned int HEADER_ENTRYPOINT = 0x0100;
enum class MBC_TYPE {
    NONE, MBC1, MBC2, MBC3, MBC5, MBC6, MBC7, M161, MMM01, HUC1, HUC3, TAMA5, UNSUPPORTED
};

struct MBC1 {
    bool ram_enable;
    bool bank_mode;
    uint8_t rom_bank_lower_5;
    uint8_t bank_upper2;
};

struct MBC2 {
    bool ram_enable;
    uint8_t rom_bank;
    std::array<uint8_t, 512> ram;
};

struct MBC3 {
    bool ram_enable;
    uint8_t rom_bank;
    uint8_t ram_bank;

    bool has_rtc;
    bool latch_ready;
    struct {
        uint8_t s;
        uint8_t m;
        uint8_t h;
        uint8_t dl;
        uint8_t dh;
    } RTC;
};

struct MBC5 {
    bool ram_enable;
    bool is_rumble;
    uint8_t rom_bank_low;
    uint8_t rom_bank_high;
    uint8_t ram_bank;
};

struct MBC6 {
    /*
     * maybe I'll implement MBC6 later, but it's only used by one game that never made it out of Japan.
     */
};

struct MBC7 {
    bool ram_enable1;
    bool ram_enable2;
    uint8_t rom_bank;
};

class Cartridge {
    public:
        Cartridge();
        ~Cartridge();
        bool load_rom(const char* filepath);
        uint8_t read_rom(uint16_t address);
        void write_rom(uint16_t address, uint8_t value);
    private:
        bool verify_header_checksum();
        MBC_TYPE get_mbc_type(uint8_t cart_type);
        void switch_bank(uint8_t bank);
        uint8_t* rom_data;
        size_t rom_size;
        size_t ram_size;
        uint8_t* rom_bank0;
        uint8_t* rom_bankX;
        uint8_t curr_bank;
        MBC_TYPE mbc_type;
        union {
            struct MBC1 mbc1;
            struct MBC2 mbc2;
            struct MBC3 mbc3;
            struct MBC5 mbc5;
            struct MBC6 mbc6;
            struct MBC7 mbc7;
        };
};
#endif
