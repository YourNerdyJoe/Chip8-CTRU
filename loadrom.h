#ifndef _LOAD_ROM_H_
#define _LOAD_ROM_H_
#include <ctr/types.h>

#define CHIP8_PATH	"/Chip8/"
#define CHIP8_PATH_LEN	8

u32 loadRom(const char* fn);

#endif
