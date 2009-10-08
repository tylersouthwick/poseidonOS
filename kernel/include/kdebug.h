#ifndef KDEBUG_H
#define KDEBUG_H

#include <screen.h>

#define DEBUG(a) MESSAGE("DEBUG", a)
#define DEBUG_HEX(a) write_integer(a, 16)

#define INFO(a) MESSAGE("INFO", a)
#define INFO_INT(a,b) write_integer(a,b)

#define ERROR(a) MESSAGE("ERROR", a)
#define ERROR_INT(a,b) write_integer(a,b)

//#define MESSAGE(t, a) getVideo()->Write(t);getVideo()->Write("[");getVideo()->Write(__FILE__);getVideo()->Write(":");getVideo()->Write(__LINE__, 10);getVideo()->Write("]: ");getVideo()->Write(a);getVideo()->Write("\n");
//#define MESSAGE(t, a) video.Write(t);video.Write("[");video.Write(__FILE__);video.Write(":");video.Write(__LINE__, 10);video.Write("]: ");video.Write(a);video.Write("\n");
#define MESSAGE(t, a) write_string(a);

#endif

