#ifndef DEVICES_MANAGER_H
#define DEVICES_MANAGER_H

typedef struct
{
	unsigned int (*read)(unsigned int, void *, unsigned int);
	unsigned int (*write)(unsigned int, void *, unsigned int);
} device_t;

void devicemanager_init(void);
void devicemanager_init_devices(void);
//void device_register(char *, unsigned long, unsigned long);
void device_register(char *dev_name, unsigned int (*read_handler)(unsigned int, void *, unsigned int), unsigned int (*write_handler)(unsigned int, void *, unsigned int));
device_t *device_get(char *);

#endif

