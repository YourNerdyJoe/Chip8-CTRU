#include "loadrom.h"
#include "chip8.h"

u32 loadRom(const char* fn)
{
	char pathstr[64];
	FS_path path = {PATH_CHAR,0,(u8*)pathstr};
	Handle f;
	u64 size;
	u32 bytesRead = 0;

	initEmu();	//restart emu
	
	sprintf(pathstr,CHIP8_PATH "%s",fn);
	path.size = strlen(pathstr) + 1;

	FSUSER_OpenFileDirectly(fsuHandle,&f,sdmcArchive,path,FS_OPEN_READ,FS_ATTRIBUTE_NONE);

	FSFILE_GetSize(f,&size);
	if(size > (MEMORY_SIZE - 0x200)) size = (MEMORY_SIZE - 0x200);

	FSFILE_Read(f,&bytesRead,0,(u32*)&Chip8.memory[0x200],size);

	FSFILE_Close(f);
	return bytesRead;
}
