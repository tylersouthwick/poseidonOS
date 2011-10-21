#ifndef KDEBUG_H
#define KDEBUG_H

#ifdef TEST
	#include <stdio.h>
	#define kprintf printf
#else
	#include <screen.h>
#endif

#define DEBUG_MSG(a) MESSAGE("DEBUG", a)

#define INFO_MSG(a) kprintf a; kprintf("\n")

#define ERROR_MSG(a) MESSAGE("ERROR", a)

#define FATAL_MSG(a) MESSAGE("FATAL", a)

#define MESSAGE(t, a) kprintf("%s [%s:%i] ", t, __FILE__, __LINE__); kprintf a; kprintf("\n")

#define assert(a) //TODO: implement
#endif

