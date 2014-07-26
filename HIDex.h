#ifndef _HID_EX_H_
#define _HID_EX_H_
#include <ctr/HID.h>

/* See http://3dbrew.org/wiki/HID_Shared_Memory */

/* Relative to HID SharedMem (default 0x10000000)*/
#define PAD_STATE_OFFSET	0x1C
#define CPAD_INFO_OFFSET	0x34
#define TOUCH_INFO_OFFSET	0xC0
/* index for hidSharedMem */
#define PAD_STATE	PAD_STATE_OFFSET>>2
#define CPAD_INFO	CPAD_INFO_OFFSET>>2
#define TOUCH_INFO	TOUCH_INFO_OFFSET>>2

typedef struct CirclePadInfo {
	s16 x,y;
} CirclePadInfo;

typedef struct TouchScreenInfo {
	u16 x,y;
	u32 contains_data;
} TouchScreenInfo;

#define REG_PAD_STATE	hidSharedMem[PAD_STATE]
#define REG_CPAD_INFO	((volatile CirclePadInfo*)&hidSharedMem[CPAD_INFO])
#define REG_TOUCH_INFO	((volatile TouchScreenInfo*)&hidSharedMem[TOUCH_INFO])
#define REG_TOUCH_INFO_RAW		(&REG_TOUCH_INFO[0])
#define REG_TOUCH_INFO_PIXEL	(&REG_TOUCH_INFO[1])

#endif
