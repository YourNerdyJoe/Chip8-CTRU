#include "timer.h"
#include <ctr/types.h>
#include <ctr/svc.h>

u64 ticksperframe = (1000000000/60);
u64 ticks = 0;

void Wait60FPS()
{
	u64 elapsed = svc_getSystemTick() - ticks;
	if(elapsed < ticksperframe)
	{
		svc_sleepThread(ticksperframe - elapsed);
	}
	ticks = svc_getSystemTick();
}
