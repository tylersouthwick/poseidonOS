#ifndef DEVICES_MANAGER_H
#define DEVICES_MANAGER_H

#define DEV_FLOPPY 0
#define DEV_FLOPPY_0 0
#define DEV_FLOPPY_1 1

void devicemanager_init(void);
void devicemanager_init_devices(void);

void device_register(char *, unsigned int, unsigned int, unsigned int, unsigned int);

typedef struct
{
	unsigned int major;
	unsigned int minor;
	unsigned int read_handler;
	unsigned int write_handler;
} device_t;

#endif

