#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>

#include "callback.h"

#include "dungeon.h"

#include "glib2d.h"

#include "intraFont.h"

#define VERS 1 
#define REVS 0

PSP_MODULE_INFO("Simple Dungeon Generator", PSP_MODULE_USER, VERS, REVS);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER); 

#define printf pspDebugScreenPrintf

int map[ROWS][COLS] = {0};

void clearMap()
{
	for(int i=0;i<ROWS;i++)
	{
		for(int j=0;j<COLS;j++)
		{
			map[i][j] = 0;
		}
	}
}

int main(void) 
{       
	pspDebugScreenInit();
	setupExitCallback();


	SceCtrlData input;

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);


	g2dInit();
	intraFontInit();

	intraFont* font;
	font = intraFontLoad("flash0:/font/ltn8.pgf",0);
	char text[256] = {'\0'};
	char instructions[256] = {'\0'};


	int space = 20;

	int tx = 10;
	int ty = 10;

	int noOfRooms = 7;

	generate(map, noOfRooms);


	while(isRunning())
	{
		tx = ty = 10;
		g2dClear(BLACK);
		
		/*handle input*/
		sceCtrlPeekBufferPositive(&input, 1); 

		if(input.Buttons != 0) 
		{ 
			if(input.Buttons & PSP_CTRL_START)
			{ 
				clearMap();
				generate(map, noOfRooms);
			} 
		}

		
		//reload results in crash
// 		sprintf(text,"No. of Rooms %d", noOfRooms);
// 		intraFontSetStyle(font, 1.f, WHITE, 0, 0, INTRAFONT_ALIGN_LEFT);
// 		intraFontPrintf(font, 5, 20, text);

// 		sprintf(instructions,"Press SELECT to generate new dungeon");
// 		intraFontSetStyle(font, 0.5f, WHITE, 0, 0, INTRAFONT_ALIGN_LEFT);
// 		intraFontPrintf(font, 250, 100, instructions);

		for(int i=0;i < ROWS;i++)
		{
			for(int j=0;j < COLS;j++)
			{
				if(map[i][j] == 0)
				{
					tx += space + 5;
				}
				else if(map[i][j] == 1)
				{
					/*start room */
					g2dBeginRects(NULL);
					g2dSetColor(YELLOW);
					g2dSetScaleWH(20, 20);
					g2dSetCoordXY(tx, ty);
					g2dAdd();
					g2dEnd();

					tx += space + 5;

				}
				else
				{
					/*other rooms*/
					g2dBeginRects(NULL);
					g2dSetColor(RED);
					g2dSetScaleWH(20, 20);
					g2dSetCoordXY(tx, ty);
					g2dAdd();
					g2dEnd();

					tx += space + 5;
				}
			}
			tx = 10;
			ty += space + 5;
		}


		g2dFlip(G2D_VSYNC);

	}
	g2dTerm();
	sceKernelExitGame();	

	return 0;
}
