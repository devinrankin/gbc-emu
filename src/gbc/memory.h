#ifndef GBC_EMU_MEM_H_
#define GBC_EMU_MEM_H_
#include <array>
#include <cstdint>

static constexpr unsigned int MEMORY_SIZE = 0xFFFF;
static constexpr unsigned int RAM_SIZE = 0x3FFF;

enum MBC_TYPE {
    NONE, MBC1, MBC2, MBC3, MBC5, MBC6, MBC7, M161, MMM01, HUC1, HUC3, TAMA5
};

struct MBC1 {
    bool ram_enable;
    bool bank_mode;
    uint8_t* rom;
    uint8_t* ram;
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
    typedef struct {
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

struct MB7 {
    bool ram_enable;

};

class Memory {
    public:
        uint8_t memory[MEMORY_SIZE];
        uint8_t ram[RAM_SIZE];
        Memory();
        ~Memory();
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);
    private:
};

#endif
