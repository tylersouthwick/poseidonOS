#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

/*device values*/
#define DEV_FLOPPY		2
#define DEV_FLOPPY_0	0
#define DEV_FLOPPY_1	1


#define DEV_MAX_COUNT 	5

void devicemanager_init();

void device_register(unsigned int major, unsigned int minor, unsigned int read_handler, unsigned int write_handler);

typedef struct
{
	unsigned int major;
	unsigned int minor;
	unsigned int read_handler;
	unsigned int write_handler;
} device_t;
#endif
