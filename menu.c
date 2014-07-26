#include "menu.h"
#include "chip8.h"

#define MAX_FILES 12

char fileNames[MAX_FILES][512];

#define BUTTON_OFFSET_X	32
#define BUTTON_HEIGHT	20

void unicode2char(u16* src,char* dst)
{
	if(!src || !dst) return;
	while(*src) *(dst++) = *(src++)&0xFF;
	*dst = 0;
}

void initFiles()
{
	Handle dir;
	FS_path path = {PATH_CHAR,CHIP8_PATH_LEN,(u8*)CHIP8_PATH};
	u32 entriesRead = 0;
	u16 entryBuf[512];
	int i;

	FSUSER_OpenDirectory(fsuHandle,&dir,sdmcArchive,path);

	for(i=0; i<MAX_FILES; i++)
	{
		int j;
		for(j=0;j<1024;j++)
		{
			fileNames[i][j] = 0;
		}

		FSDIR_Read(dir,&entriesRead,1,entryBuf);
		if(entriesRead == 0) break;

		unicode2char(entryBuf,fileNames[i]);
	}

	FSDIR_Close(dir);
}

void drawFiles()
{
	clear_screen(0,0,0,bottomBuffer);

	if(fileNames[0][0] == 0)
	{
		draw_string("No files in /Chip8",16,16,255,255,255,bottomBuffer);
	}
	else
	{
		int i;
		for(i=0; i<MAX_FILES; i++)
		{
			int center;
			size_t len;

			if(fileNames[i][0] == 0) break;
			draw_fillrect(BUTTON_OFFSET_X,i*BUTTON_HEIGHT+1,320-BUTTON_OFFSET_X,i*BUTTON_HEIGHT+BUTTON_HEIGHT-1,40,40,40,bottomBuffer);
			
			len = strlen(fileNames[i]);
			center = 160 - (len*4);
			draw_string(fileNames[i],center,i*BUTTON_HEIGHT+(BUTTON_HEIGHT-8)/2,255,255,255,bottomBuffer);
		}
	}

	swap_bottom();
}

u32 wasScreenTouched = 0;

void updateMenu()
{
	volatile TouchScreenInfo* touch = REG_TOUCH_INFO_PIXEL;
	if(!wasScreenTouched && touch->contains_data)
	{
		if(	touch->x >= BUTTON_OFFSET_X &&
			touch->x <= 320-BUTTON_OFFSET_X )
		{
			int index = touch->y / BUTTON_HEIGHT;
			if(fileNames[index][0] != 0)
			{
				loadRom(fileNames[index]);
				//{
				//	draw_string("Unable to load /Chip8/game.c8",16,16,255,255,255,bottomBuffer);
				//	swap_bottom();
				//}
			}
		}
	}

	wasScreenTouched = touch->contains_data;
}
