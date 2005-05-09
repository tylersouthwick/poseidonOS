/* File: screen.h
   Description: provide prototypes for the global functions referenced in screen.c*/

#ifndef SCREEN_H
#define SCREEN_H

void kprint(char *str);
void screen_clear(void);
void put_char(char c);
void put_int(int num, int base);
void screen_set_color(int color);

#define converToPos(a,b) 2*(80*b+a)

/******************************Colors************************************/
#define SCREEN_BLINK		2<<7
	
#define SCREEN_FG_BLACK						0x00
#define SCREEN_FG_BLUE						0x01
#define SCREEN_FG_GREEN						0x02
#define SCREEN_FG_CYAN						0x03
#define SCREEN_FG_RED							0x04
#define SCREEN_FG_MAGENTA					0x05
#define SCREEN_FG_BROWN						0x06
#define SCREEN_FG_WHITE						0x07
#define SCREEN_FG_DARK_GREY				0x08
#define SCREEN_FG_BRIGHT_BLUE			0x09
#define SCREEN_FG_BRIGHT_GREEN		0x0A
#define SCREEN_FG_BRIGHT_CYAN			0x0B
#define SCREEN_FG_PINK						0x0C
#define SCREEN_FG_BRIGHT_MAGENTA	0x0D
#define SCREEN_FG_YELLOW					0x0E
#define SCREEN_FG_BRIGHT_WHITE		0x0F

#define SCREEN_BG_BLACK						0x00
#define SCREEN_BG_BLUE						0x10
#define SCREEN_BG_GREEN						0x20
#define SCREEN_BG_CYAN						0x30
#define SCREEN_BG_RED							0x40
#define SCREEN_BG_MAGENTA					0x50
#define SCREEN_BG_BROWN						0x60
#define SCREEN_BG_WHITE						0x70

#define SCREEN_DEFAULT		SCREEN_BG_BLACK | SCREEN_FG_WHITE

#endif
