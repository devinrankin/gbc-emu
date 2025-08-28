#ifndef GBC_EMU_CART_H_
#define GBC_EMU_CART_H_
#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include "cartridge_header.h"

class Cartridge {
    public:
        Cartridge();
        ~Cartridge();
        bool load_rom(const char* filepath);
        virtual uint8_t read(uint16_t address);
        virtual void write(uint16_t address, uint8_t value);
    protected:
        std::unique_ptr<CartridgeHeader> header;
        void switch_bank(uint8_t bank);

        std::vector<uint8_t> rom_data;
        std::vector<uint8_t> ram_data;
};

class NoMBC : public Cartridge {
    NoMBC(std::unique_ptr<CartridgeHeader> header, std::vector<uint8_t> rom_data, std::vector<uint8_t> ram_data);

    uint8_t read(const uint16_t address) override;
    void write(const uint16_t address, uint8_t value) override;
};

class MBC1 : public Cartridge {
public:
    MBC1(std::unique_ptr<CartridgeHeader> header, std::vector<uint8_t> rom_data, std::vector<uint8_t> ram_data, std::unique_ptr<CartridgeHeader> cartridge_header);
    uint8_t read(const uint16_t address) override;
    void write(const uint16_t address, uint8_t value) override;
private:
    bool ram_enabled = false;
    uint8_t bank = 0;
    bool bank_mode = 0;
};

class MBC2 : public Cartridge {
public:
    MBC2(std::unique_ptr<CartridgeHeader> header, std::vector<uint8_t> rom_data, std::unique_ptr<CartridgeHeader> cartridge_header);
    uint8_t read(const uint16_t address) override;
    void write(const uint16_t address, uint8_t value) override;
private:
    bool ram_enabled = false;
    uint8_t bank = 0;
    std::array<uint8_t, 512> ram;
};

class MBC3 : public Cartridge {
public:
    MBC3(std::unique_ptr<CartridgeHeader> header, std::vector<uint8_t> rom_data, std::vector<uint8_t> ram_data, std::unique_ptr<CartridgeHeader> cartridge_header);
    uint8_t read(const uint16_t address) override;
    void write(const uint16_t address, uint8_t value) override;
private:
    bool ram_enabled = false;
    uint8_t bank = 0;
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

class MBC5 : public Cartridge {
public:
    MBC5(std::unique_ptr<CartridgeHeader> header, std::vector<uint8_t> rom_data, std::vector<uint8_t> ram_data, std::unique_ptr<CartridgeHeader> cartridge_header);
    uint8_t read(const uint16_t address) override;
    void write(const uint16_t address, uint8_t value) override;
private:
    bool ram_enabled = false;
    uint8_t bank = 0;
};

class MBC7 : public Cartridge {
public:
    MBC7(std::unique_ptr<CartridgeHeader> header, std::vector<uint8_t> rom_data, std::vector<uint8_t> ram_data, std::unique_ptr<CartridgeHeader> cartridge_header);
    uint8_t read(const uint16_t address) override;
    void write(const uint16_t address, uint8_t value) override;
private:
    bool ram_enabled = false;
    uint8_t bank = 0;
};


#endif
