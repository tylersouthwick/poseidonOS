#ifndef MUTEX_H
#define MUTEX_H

struct mutex {
	bool locked;
} mutex_t;


static inline void mutex_initialize(mutext *mutex, bool locked) {
}

void mutex_lock(mutext *mutex);

void mutex_unlock(mutext *mutex);
#endif
