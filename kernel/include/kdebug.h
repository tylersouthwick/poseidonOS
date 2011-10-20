#ifndef KDEBUG_H
#define KDEBUG_H

#ifdef TEST
	#include <stdio.h>
	#define kprintf printf
#else
	#include <screen.h>
#endif

#define DEBUG(a) MESSAGE("DEBUG", a)

#define INFO(a) kprintf a; kprintf("\n")

#define ERROR(a) MESSAGE("ERROR", a)

#define FATAL(a) MESSAGE("FATAL", a)

#define MESSAGE(t, a) kprintf("%s [%s:%i] ", t, __FILE__, __LINE__); kprintf a; kprintf("\n")

#define assert(a) //TODO: implement
#endif

