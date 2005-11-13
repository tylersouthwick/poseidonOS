/* File: screen.c
   Description: Implements rudimentary access to the console screen*/

#include <ktypes.h>
#include <kdebug.h>

#include <bios.h>
#include <string.h>
#include <screen.h>

/****************************** Internal Functions and Variables **************************/
static unsigned char *video_mem = (unsigned char *)0xB8000;
static int scr_x=0, scr_y=0;
static unsigned char screen_attributes=SCREEN_FG_WHITE | SCREEN_BG_BLACK;

static void kprint_str(char *);
static void update_cursor(void);
/*****************************************************************************************/

/******************************* Macros **************************/
//Control Characters
#define TAB 4		//how many spaces to display when given the '\t' character
/****************************************************************/

static inline int screen_get_position(void) {
	return 2*(scr_y*80+scr_x);
}

static void update_cursor() {
	unsigned temp;
	
	//update cursor pos
	temp = scr_y*80+scr_x;
	outportb(crtc_io_adr+0, 14);
	outportb(crtc_io_adr+1, temp >> 8);
	outportb(crtc_io_adr+0, 15);
	outportb(crtc_io_adr+1, temp);
}

void put_char(char c)
{
	switch (c)
	{
		case '\n':
		{
			scr_y++;
			scr_x = 0;
			break;
		}
		case '\b':
		{
			if (scr_x - 1 < 0)
			{
				if (scr_y > 0)
					scr_y--;
				scr_x = 79;
			} else {
				scr_x--;
			}
			video_mem[screen_get_position()] = 0;
			video_mem[screen_get_position()+1] = screen_attributes;
			break;
		}
		case '\t':
		{
			scr_x++;
			video_mem[screen_get_position()] = 0;
			video_mem[screen_get_position()+1] = screen_attributes;
			scr_x++;
			video_mem[screen_get_position()] = 0;
			video_mem[screen_get_position()+1] = screen_attributes;
			break;
		}
		default:
		{
			video_mem[screen_get_position()] = c;
			video_mem[screen_get_position()+1] = screen_attributes;
			scr_x++;
			break;
		}
	}

	if (scr_x==80) { scr_x=0; scr_y++;}
	if (scr_y==25) {
		memcpy(video_mem,(void *)((int)video_mem + 160), 4000);
		scr_y--;
	}
	update_cursor();
}

void put_int(unsigned int number, unsigned int base)
{
	int index = 0;
	char buffer1[12];
	char buffer2[12];

	if (number < 0)
	{
		put_char('-');
		number *= -1;
	}

	if (base == 0x10)
	{
		put_char('0');
		put_char('x');
	}

	if (!number)
	{
		put_char('0');
		return;
	}

	memset(buffer1, 0, 12);
	memset(buffer2, 0, 12);
 
	do
	{
		int digit = number % base;
		char ch;

		if (digit < 10)
			ch = '0' + (number % base);
		else
			ch =  'A' + (number % base) - 10 ;

		buffer1[index++] = ch;
	} while (number /= base);

	{
		int length = strlen(buffer1);
		int i;
		for (i=0; i<length; i++)
			buffer2[i] = buffer1[length-i - 1];
	}

	kprint(buffer2);
}

void kprint(char *str) {
	kprint_str(str);
}

static void kprint_str(char *str) {
	int h=0,i;
	char c;
	while (*(str+h) != '\0') {
		switch (c=*(str+h)) {
			case '\t':
				for (i=1; i<=TAB; i++)
					put_char(32);
				break;
			default:
				put_char(*(str+h));
				break;
		}
		h++;
	}
	update_cursor();
}

void screen_clear() {
	unsigned int i=0;
	while (i< (80*25*2))
	{
		video_mem[i] = ' ';
		i++;
		video_mem[i] = screen_attributes;
		i++;
	};
	scr_x=scr_y=0;
	update_cursor();
}

void screen_set_color(int color)
{
	screen_attributes = color;
}
