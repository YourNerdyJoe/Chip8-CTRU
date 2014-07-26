#include "draw.h"
#include "ascii64.h"
#include <string.h>
#include "chip8.h"

extern u8* topLeftBuffer;
extern u8* topRightBuffer;
extern u8* bottomBuffer;

void clear_screen(char r, char g, char b, u8* screen)
{
	int width;
	if(screen == bottomBuffer)
		width = SUB_SCREEN_WIDTH;
	else
		width = MAIN_SCREEN_WIDTH;

	u32 x,y;
	for(x = 0; x < width; x++)
	{
		for(y = 0; y < 240; y++)
		{
			u32 scr_pix = (x*240+y)*3;
			screen[scr_pix+0] = b;
			screen[scr_pix+1] = g;
			screen[scr_pix+2] = r;
		}
	}
}

//No double buffing on top screen
//screws up 3d when app was launched in 2d
void swap_top()
{
	GSPGPU_FlushDataCache(NULL,gspHeap,MAIN_FRAMEBUFFER_SIZE*2);

	//copy top left
	GX_RequestDma(gxCmdBuf,(u32*)topLeftBuffer,(u32*)topLeftFramebuffers[currentTopBuffer],MAIN_FRAMEBUFFER_SIZE);
	//copy top right
	GX_RequestDma(gxCmdBuf,(u32*)topRightBuffer,(u32*)topRightFramebuffers[currentTopBuffer],MAIN_FRAMEBUFFER_SIZE);
}

void swap_bottom()
{
	u32 copiedFramebuffer = currentBottomBuffer^1;
	GSPGPU_FlushDataCache(NULL,bottomBuffer,SUB_FRAMEBUFFER_SIZE);

	//copy bottom
	GX_RequestDma(gxCmdBuf,(u32*)bottomBuffer,(u32*)bottomFramebuffers[copiedFramebuffer],SUB_FRAMEBUFFER_SIZE);

	//swap buffers
	u32 regData;
	GSPGPU_ReadHWRegs(NULL,REG_SUBFB_SELECT,&regData,4);
	regData ^= 1;
	currentBottomBuffer = regData&1;
	GSPGPU_WriteHWRegs(NULL,REG_SUBFB_SELECT,&regData,4);
}

/* taken and adapted from nop90's 3DS_Homebrew */

void draw_pixel(int x, int y, char r, char g, char b, u8* screen)
{
    int coord = 720*x+720-(y*3)-3;
    screen[coord+0] = b;
	screen[coord+1] = g;
	screen[coord+2] = r;
}

void draw_char(char letter,int x,int y, char r, char g, char b, u8* screen)
{
  int i, k;
  unsigned char mask;
  unsigned char l;

  for (i = 0; i < 8; i++){
    mask = 0b10000000;
    l = ascii_data[letter][i];
    for (k = 0; k < 8; k++){
      if ((mask >> k) & l){
        draw_pixel(k+x,i+y,r,g,b,screen);
      }     
    }
  }
}

void draw_string(char* word, int x,int y, char r, char g, char b, u8* screen)
{
	int tmp_x =x;
	int i;
	int line = 0;

	int width;

	if(screen == bottomBuffer)
		width = SUB_SCREEN_WIDTH;
	else
		width = MAIN_SCREEN_WIDTH;

	size_t len = strlen(word);
	for (i = 0; i < len; i++)
	{
		if (tmp_x+8 > width) {
			line++;
			tmp_x = x;
		}
		draw_char(word[i],tmp_x,y+(line*8),r,g,b, screen);

		tmp_x = tmp_x+8;
	}
}

void draw_fillrect(int x1, int y1, int x2, int y2, char r, char g, char b, u8* screen)
{
	int i,j;
	for(i=x1;i<=x2;i++){
		for(j=y1;j<=y2;j++){
			draw_pixel(i,j, r, g, b, screen);
		}
	}
}
