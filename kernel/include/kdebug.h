#ifndef KDEBUG_H
#define KDEBUG_H

#include <screen.h>

#define KLOG_INFO(a) kprint(a)
#define KLOG_INT_INFO(a,b) put_int(a,b)

#ifdef DEBUG
  #define KDEBUG(a) kprint(a)
  #define KDEBUG_HEX(a) put_int(a, 16)
#else
  #define KDEBUG(a)
  #define KDEBUG_HEX(a)
#endif

#define KLOG_ERROR(a) kprint(a)
#define KLOG_INT_ERROR(a,b) put_int(a,b)

#endif

