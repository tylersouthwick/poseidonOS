#ifndef KDEBUG_H
#define KDEBUG_H

#include <screen.h>

#define KLOG_INFO(a) kprint(a)
#define KLOG_INT_INFO(a,b) put_int(a,b)

#define KLOG_DEBUG(a) /*kprint(a)*/
#define KLOG_INT_DEBUG(a,b) /*put_int(a,b)*/

#define KDEBUG(a) kprint(a)

#define KLOG_ERROR(a) kprint(a)
#define KLOG_INT_ERROR(a,b) put_int(a,b)

#endif

