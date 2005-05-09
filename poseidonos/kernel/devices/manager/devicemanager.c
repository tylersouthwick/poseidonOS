#include <kernel.h>
#include <kutil.h>					/*for all map related functions*/
#include <kdebug.h>					/*for all map related functions*/

#include <devicemanager.h>
#include <devices.h>

#include <util/map.h>

map_t *device_map;

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
	device_map = linked_list_map_create();
}


/*******************************************************************************
 * void devicemanager_init_devices()
 *
 * *****************************************************************************/
void devicemanager_init_devices()
{
	screen_set_color(SCREEN_FG_CYAN | SCREEN_BG_BLACK);
	kprint("floppy ");
	screen_set_color(SCREEN_DEFAULT);
	floppy_init();
	screen_set_color(SCREEN_FG_CYAN | SCREEN_BG_BLACK);
	kprint("keyboard ");
	screen_set_color(SCREEN_DEFAULT);
	keyboard_init();
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
void device_register(char *dev_name, unsigned int major, unsigned int minor, 
					unsigned int read_handler, unsigned int write_handler)
{
	device_t * new_device = kmalloc(sizeof(device_t));
	new_device->major = major;
	new_device->minor = minor;
	new_device->read_handler = read_handler;
	new_device->write_handler = write_handler;
	
	device_map->add(device_map, dev_name, new_device, sizeof(device_t));

#ifdef DEBUG_DEVICEMANAGER
	kprint("registered device ");
	put_int(major,10);
	kprint(",");
	put_int(minor,10);
	kprint("\n");
#endif
}

