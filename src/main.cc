#include "gbc/gbc.h"
#include <stdio.h>

int main(int argc, char** argv) {
    GBColor gbc;

    gbc.load_rom("../test-roms/pkmn_silver.gbc");
    printf("%x\n", gbc.cartridge->rom_data[0]);
    return 0;
}
