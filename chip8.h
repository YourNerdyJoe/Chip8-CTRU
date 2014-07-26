/**********************************
* CHIP 8 - Homebrew 3DS Rev 0.00.1*
*            S4rk                 *
***********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctr/types.h>
#include <ctr/GSP.h>
#include <ctr/GX.h>
#include "LCD.h"
#include <ctr/srv.h>
#include <ctr/svc.h>
#include "svcex.h"
#include <ctr/APT.h>
#include <ctr/HID.h>
#include "HIDex.h"
#include "draw.h"
#include "cfgmem.h"
#include <ctr/FS.h>
#include "FSex.h"
#include "loadrom.h"
#include "timer.h"

#define MAIN_FRAMEBUFFER_SIZE (MAIN_SCREEN_SIZE*3)
#define SUB_FRAMEBUFFER_SIZE (SUB_SCREEN_SIZE*3)
#define OFFSET_3D	3
#define PIXEL_SIZE	6

#define SCREEN_SIZE 2048
#define REG_T 16
#define STACK_SIZE 16
#define GAME_PAD 16
#define MEMORY_SIZE 4096
#define FONT_SET 80

typedef unsigned char BYTE;
typedef unsigned short DWORD;
//typedef char bool;
//typedef enum{true, false};
typedef struct _Chip8 _Chip8;

struct _Chip8{
    DWORD opcode;
    BYTE reg[REG_T];
    BYTE memory[MEMORY_SIZE];

    DWORD REG_I;
    DWORD PC;

    DWORD stack[STACK_SIZE];
    DWORD stack_pointer;

    bool drawFlag;
    bool inGame;

    BYTE gamePad[GAME_PAD];
    BYTE gameScreen[SCREEN_SIZE];
};

_Chip8 Chip8;

extern u16 keyReg[GAME_PAD];

extern u8* topLeftFramebuffers[2];
extern u8* topRightFramebuffers[2];
extern u8* bottomFramebuffers[2];
extern u8 currentTopBuffer,currentBottomBuffer;

extern Handle gspEvent,gspSharedMemory;
extern u8* gspHeap;
extern u32* gxCmdBuf;

extern u8* topLeftBuffer;
extern u8* topRightBuffer;
extern u8* bottomBuffer;

extern Handle fsuHandle;
extern FS_archive sdmcArchive;

void initEmu();
void initHW();
void exitHW();
void getFramebuffers();
void gspGpuInit();
void gspGpuExit();
void instruEmu();
//void loopEmu();
//void loadROM();
void drawGrf();
void gameKey();

