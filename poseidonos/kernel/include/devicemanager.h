#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

/*device values
 * this are deprecated (i know-
 * i haven't even released one
 * versino yet :)*/
#define DEV_FLOPPY		2
#define DEV_FLOPPY_0	0
#define DEV_FLOPPY_1	1

void devicemanager_init();
void devicemanager_init_devices();

void device_register(char *dev_name, unsigned int major, unsigned int minor, unsigned int read_handler, unsigned int write_handler);

typedef struct
{
	unsigned int major;
	unsigned int minor;
	unsigned int read_handler;
	unsigned int write_handler;
} device_t;

#endif
