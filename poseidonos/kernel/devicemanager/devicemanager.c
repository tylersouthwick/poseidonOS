#include <ktypes.h>
#include <devicemanager.h>
#include <kmalloc.h>
#include <screen.h>

device_t *devices;
int dev_count;

/*******************************************************************************
 * void devicemanager_init()
 * 
 * This is the devicemanager and sets up the kernel hooks for different devices.
 * I'm still trying to think of a good data structure (dynamic structure) that
 * would be best to use here...  At present, it just allocated space for a static
 * amount of devices, which is a temporary fix :).
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	December 20, 2004
 * *****************************************************************************/
void devicemanager_init()
{	
	kprint("\n\tsetting up device table...\n");
	
	devices = (device_t *)kmalloc(sizeof(device_t)*DEV_MAX_COUNT);
	dev_count = 0;
		
	kprint("\tallocated space for ");
	put_int(DEV_MAX_COUNT, 10);
	kprint(" devices\n");
}

/*******************************************************************************
 * void device_register(unsigned int major, unsigned int minor, 
 * 			unsigned int read_handler, unsigned int write_handler)
 * 
 * This is how a device is registered with the kernel.  It mimics the linux standard
 * of major and minor numbers (which are defined in devices.h).  When a request
 * comes to read or write to a device, it is looked up here, and the data is pushed
 * onto the stack and then either the read_handler or write_handler (respectably),
 * is called and performs the desired action.
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	December 18, 2004
 * *****************************************************************************/
void device_register(unsigned int major, unsigned int minor, 
					unsigned int read_handler, unsigned int write_handler)
{
	devices[dev_count].major = major;
	devices[dev_count].minor = minor;
	devices[dev_count].read_handler = read_handler;
	devices[dev_count].write_handler = write_handler;
	dev_count++;
	
	kprint("registered device ");
	put_int(major,10);
	kprint(",");
	put_int(minor,10);
	kprint("\n");
	
}

