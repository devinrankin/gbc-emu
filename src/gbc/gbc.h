#ifndef GBC_EMU_CORE_H_
#define GBC_EMU_CORE_H_

#include "cpu.h"
#include "memory.h"
#include "cartridge.h"

class GBColor {
    public:
        GBColor();
        ~GBColor();
        bool load_rom(const char* filename);
        void emulate();

        CPU* cpu;
        Memory* memory;
        Cartridge* cartridge;
    private:
};

#endif
