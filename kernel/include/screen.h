/* File: screen.h
   Description: provide prototypes for the global functions referenced in screen.c*/

#ifndef SCREEN_H
#define SCREEN_H

//Control Characters
#define TAB 4		//how many spaces to display when given the '\t' character

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

void initScreen();
void clear_screen();
void set_screen_color(int color);
void write_base10(int number);
void write_integer(unsigned int number, unsigned int base);
void write_char(char c);
void write_string(char *c);

void kprintf(const char *format, ...);

#endif
