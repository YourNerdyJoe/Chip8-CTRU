/***********************************
* Chip8-CTRU                       *
* Chip 8 Homebrew Emulator for 3DS *
*       St4rk, YourNerdyJoe        *
***********************************/
#include "chip8.h"
#include "loadrom.h"
#include "menu.h"

int main(int argc, char **argv){
	u32 regData;

    initEmu();

	initHW();

	FSUSER_OpenArchive(fsuHandle,&sdmcArchive);

	initFiles();
	drawFiles();
	
	//loopEmu();
	APP_STATUS status;
	while((status=aptGetStatus()) != APP_EXITING)
	{
		switch(status)
		{
		case APP_RUNNING:
			updateMenu();
			if(Chip8.inGame == true)
			{
				instruEmu();
				gameKey();
				drawGrf();
			}
			break;

		case APP_SUSPENDING:
			aptReturnToMenu();
			//redraw bottom screen when app resumes
			drawFiles();
			Chip8.drawFlag = true;
			break;

		case APP_SLEEPMODE:
			aptWaitStatusEvent();
			//redraw bottom screen when app resumes
			drawFiles();
			Chip8.drawFlag = true;
			break;
		}
	}

	FSUSER_CloseArchive(fsuHandle,&sdmcArchive);
	exitHW();
    return 0;
}
