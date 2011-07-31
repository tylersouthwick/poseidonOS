#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex.h>

struct semaphore {
	unsigned int count;
	mutex_t mutex;
} typedef semaphore_t;

static inline void semaphore_initialize(semaphore_t *semaphore, unsigned int count) {
	mutex_initialize(&(semaphore->mutex), 0);
	semaphore->count = count;
}

static inline void semaphore_acquire(semaphore_t *semaphore) {
	bool aquired = false;
	while (!aquired) {
		mutex_lock(&(semaphore->mutex));
		if (semaphore->count > 0) {
			semaphore->count--;
			aquired = true;
		}
		mutex_unlock(&(semaphore->mutex));
	}
}

static inline void semaphore_release(semaphore_t *semaphore) {
	mutex_lock(&(semaphore->mutex));
	semaphore->count++;
	mutex_unlock(&(semaphore->mutex));
}

#endif
