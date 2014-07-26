#ifndef _DRAW_H_
#define _DRAW_H_
#include <ctr/types.h>
#include "LCD.h"

void clear_screen(char r, char g, char b, u8* screen);
void swap_top();
void swap_bottom();
void draw_pixel(int x, int y, char r, char g, char b, u8* screen);
void draw_char(char letter,int x,int y, char r, char g, char b, u8* screen);
void draw_string(char* word, int x,int y, char r, char g, char b, u8* screen);
void draw_fillrect(int x1, int y1, int x2, int y2, char r, char g, char b, u8* screen);

#endif
