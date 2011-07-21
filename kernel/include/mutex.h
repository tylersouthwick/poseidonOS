#ifndef MUTEX_H
#define MUTEX_H

#include <ktypes.h>

struct mutex {
	bool locked;
} typedef mutex_t;


static inline void mutex_initialize(mutex_t *mutex, bool locked) {
	mutex->locked = locked;
}

void mutex_lock(mutex_t *mutex);

void mutex_unlock(mutex_t *mutex);
#endif
