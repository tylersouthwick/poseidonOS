/* File: screen.h
   Description: provide prototypes for the global functions referenced in screen.c*/

#ifndef SCREEN_H
#define SCREEN_H

void kprint(char *str);
void clear_screen();
void put_char(char c);
void put_int(int num, int base);

int scr_getPos();
void scr_setPos(int num);

#define converToPos(a,b) 2*(80*b+a)
#endif
