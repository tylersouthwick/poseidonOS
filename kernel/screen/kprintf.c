#include <screen.h>
#include <stdarg.h>

void kprintf(const char *format, ...) {
    const char *p;
    va_list argp;

    va_start(argp, format);
    for (p = format; *p != '\0'; p++) {
        if (*p != '%') {
            write_char(*p);
            continue;
        }

        switch(*++p)
        {
            case 'c': 
                {
                    //print character
                    int c = va_arg(argp, int);
                    write_char(c);
                    break;
                }
            case 'd':
            case 'i':
                {
                    //print integer
                    int i = va_arg(argp, int);
                    write_base10(i);
                    break;
                }
            case 's':
                {
                    //print string
                    char * s = va_arg(argp, char *);
                    write_string(s);
                    break;
                }
            case 'x':
                {
                    //print an integer as hex
                    int i = va_arg(argp, int);
                    write_integer(i, 16);
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
