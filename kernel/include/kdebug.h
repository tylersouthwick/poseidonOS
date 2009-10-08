#ifndef KDEBUG_H
#define KDEBUG_H

#include <screen.h>

#define DEBUG(a) MESSAGE("DEBUG", a)

#define INFO(a) kprintf a; write_char('\n')

#define ERROR(a) MESSAGE("ERROR", a)

#define FATAL(a) MESSAGE("FATAL", a)

#define MESSAGE(t, a) kprintf("%s [%s:%i] ", t, __FILE__, __LINE__); kprintf a; write_char('\n')

#endif

