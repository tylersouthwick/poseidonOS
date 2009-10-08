#include <screen.h>
#include <string.h>

//extern int scr_y, scr_x;
#define getPosition() 2*(scr_y*80+scr_x)

void write_string(char *str) {
	int h=0,i;
	char c;
	for (h=0; *(str+h) != '\0'; h++) {
		switch (c=*(str+h)) {
			case '\t':
				for (i=1; i<=TAB; i++)
					write_char((char)32);
				break;
			default:
				write_char(*(str+h));
				break;
		}
	}
    update_cursor();
}

void write_base10(int number) {
    return write_integer(number, 10);
}

void write_integer(unsigned int number, unsigned int base) {
	int index = 0;
	char buffer1[12];
	char buffer2[12];

	if (number < 0) {
		write_char('-');
		number *= -1;
	}

	if (base == 0x10) {
		write_char('0');
		write_char('x');
	}

	if (!number) {
		return write_char('0');
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
        int i;
		int length = strlen(buffer1);
		for (i=0; i<length; i++)
			buffer2[i] = buffer1[length-i - 1];
	}

	return write_string(buffer2);
}

void write_char(char c) {
	switch (c) {
		case '\n': {
			scr_y++;
			scr_x = 0;
			break;
		}
		case '\b': {
			if (scr_x - 1 < 0) {
				if (scr_y > 0) {
					scr_y--;
				}
				scr_x = 79;
			} else {
				scr_x--;
			}
			video_mem[getPosition()] = 0;
			video_mem[getPosition()+1] = screenAttributes;
			break;
		}
		case '\t': {
			scr_x++;
			video_mem[getPosition()] = 0;
			video_mem[getPosition()+1] = screenAttributes;
			scr_x++;
			video_mem[getPosition()] = 0;
			video_mem[getPosition()+1] = screenAttributes;
			break;
		}
		default: {
			video_mem[getPosition()] = c;
			video_mem[getPosition()+1] = screenAttributes;
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
