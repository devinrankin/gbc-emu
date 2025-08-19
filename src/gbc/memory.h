#include <array>
#include <cstdint>



enum MBC_TYPE {
    NONE, MBC1, MBC2, MBC3, MBC5, MBC6, MBC7, M161, MMM01, HUC1, HUC3, TAMA5
};

struct MBC1 {
    uint8_t rom_bank_lower_5;
    uint8_t bank_upper2;
    bool bank_mode;
    bool ram_enabled;
};

struct MBC2 {
    uint8_t rom_bank;
    std::array<uint8_t, 512> ram;
    bool ram_enabled;
};

struct MBC3 {
    uint8_t rom_bank_lower_5;
    uint8_t bank_upper2;

};

class Memory {
    public:
        Memory();
        ~Memory();
    private:
};
