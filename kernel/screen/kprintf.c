#include <screen.h>
#include <stdarg.h>

void kprintf(const char *format, ...) {
	const char *p;
	va_list argp;
	int padding = 0;
	char padding_char = 0;

	va_start(argp, format);
	for (p = format; *p != '\0'; p++) {
		if (*p != '%') {
			write_char(*p);
			continue;
		}

		padding_char = ' ';
		if (*(p + 1) == '0') {
			p++;
			padding_char = '0';
		}

		padding = 0;
		if (*(p + 1) >= '1' && *(p + 1) <= '9') {
			p++;
			padding = *p - '0';
		}

		switch(*++p) {
			case 'c': {
				//print character
				int c = va_arg(argp, int);
				write_char(c);
				break;
			}
			case 'd':
			case 'i': {
				//print integer
				int i = va_arg(argp, int);
				pad_unsigned_number(i, 10, padding_char, padding);
				break;
			}
			case 's': {
				//print string
				char * s = va_arg(argp, char *);
				write_string(s);
				break;
			}
			case 'x': {
				//print an integer as hex
				int i = va_arg(argp, int);
				pad_unsigned_number(i, 16, padding_char, padding);
				break;
			}
			case 'o': {
				//print an integer as hex
				int i = va_arg(argp, int);
				pad_unsigned_number(i, 8, padding_char, padding);
				break;
			}
			case '%':
				//print '%'
				write_char('%');
				break;
		}
	}

	va_end(argp);
}
