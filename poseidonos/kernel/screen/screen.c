/* File: screen.c
   Description: Implements rudimentary access to the console screen*/
#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>

/****************************** Internal Functions and Variables **************************/
unsigned char *video_mem = (unsigned char *)0xB8000;
int scr_x=0, scr_y=0;
unsigned char screen_attributes=SCREEN_FG_WHITE | SCREEN_BG_BLACK;

void kprint_str(char *str);
void update_cursor();
/*****************************************************************************************/
/******************************* Macros **************************/
//Control Characters
#define TAB 4		//how many spaces to display when given the '\t' character
/****************************************************************/

int scr_getPos() {
	return 2*(scr_y*80+scr_x);
}

void scr_setPos(int num) {
	scr_y = num/160;
	scr_x = (num/2) % 80;
	update_cursor();
}

void update_cursor() {
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

	if (c == '\n') {
		scr_y++;
		scr_x = 0;
		goto reset_screen;
	}
	
	video_mem[scr_getPos()] = c;
	video_mem[scr_getPos()+1] = screen_attributes;
	scr_x++;

	reset_screen:
	if (scr_x==80) { scr_x=0; scr_y++;}
	if (scr_y==25) {
		memcpy(video_mem,(void *)((int)video_mem + 160), 4000);
		scr_y--;
	}
	update_cursor();
}
void put_int(int num, int base)
{
	char nstr[12];
	char *buf;
	int i=10;
	
	if (num < 0) {
		put_char('-');
		//x+=1;
		num = -1 * num;
	}
	if (base == 16) {
		put_char('0');
		put_char('x');
	}
	if (num == 0) {
		put_char('0');
		//x+=1;
		return;
	}


	memset(nstr,12,0);

	while(i >= 0) {
		if ((num % base) > 9)
			nstr[i] = 'A' + (num  % base) -10;
		else
			nstr[i] = '0' + (num  % base);
		num /= base;
		i--;
	}

	buf = (char *)&nstr;
	while (*(buf) == '0')
		buf++;
	kprint_str(buf);

}
void kprint(char *str) {
	kprint_str(str);
}
void kprint_str(char *str) {
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
//void screen_init() {

void screen_set_color(int color)
{
	screen_attributes = color;
}
