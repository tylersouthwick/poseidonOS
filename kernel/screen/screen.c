/* File: screen.c
   Description: Implements rudimentary access to the console screen*/

#include <ktypes.h>

#include <bios.h>
#include <string.h>
#include <screen.h>

int screenAttributes;
int scr_x, scr_y;
unsigned char *video_mem;

void initScreen() {
	video_mem = (unsigned char *)0xB8000;
	scr_x = scr_y = 0;
	screenAttributes=SCREEN_FG_WHITE | SCREEN_BG_BLACK;
}

void clear_screen() {
	unsigned int i=0;
	while (i< (80*25*2)) {
		video_mem[i] = ' ';
		i++;
		video_mem[i] = screenAttributes;
		i++;
	};
	scr_x=scr_y=0;
	update_cursor();
}
