#ifndef KDEBUG_H
#define KDEBUG_H

//#define DEBUG_MM
//#define DEBUG_MULTITASKING
//#define DEBUG_DEVICEMANAGER
//
#define KLOG_INFO(a) kprint(a)
#define KLOG_INT_INFO(a,b) put_int(a,b)
#define KLOG_DEBUG(a) kprint(a)
#define KLOG_INT_DEBUG(a,b) put_int(a,b)

#endif

