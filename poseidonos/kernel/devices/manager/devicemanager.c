#include <kernel.h>
#include <kutil.h>					/*for all map related functions*/
#include <kdebug.h>					/*for all map related functions*/

#include <devices/manager.h>
#include <devices/floppy.h>
#include <devices/keyboard.h>

#include <util/map.h>

static map_t *device_map;

/*******************************************************************************
 * void devicemanager_init()
 * 
 * This is the devicemanager and sets up the kernel hooks for different devices.
 * I'm still trying to think of a good data structure (dynamic structure) that
 * would be best to use here...  At present, it just allocated space for a static
 * amount of devices, which is a temporary fix :).
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
	floppy_init();
	screen_set_color(SCREEN_FG_CYAN | SCREEN_BG_BLACK);
	kprint("floppy ");
	screen_set_color(SCREEN_DEFAULT);

	screen_set_color(SCREEN_FG_CYAN | SCREEN_BG_BLACK);
	kprint("keyboard ");
	screen_set_color(SCREEN_DEFAULT);
	keyboard_init();
}

/*******************************************************************************
 * void device_register(char *dev_name, void (*read_handler)(), void (*write_handler)())
 * 
 * This is how a device is registered with the kernel.  When a request
 * comes to read or write to a device, it is looked up here, and the data is pushed
 * onto the stack and then either the read_handler or write_handler (respectably),
 * is called and performs the desired action.
 * *****************************************************************************/
void device_register(char *dev_name, unsigned int (*read_handler)(unsigned int, void *, unsigned int), unsigned int (*write_handler)(unsigned int, void *, unsigned int))
{
	device_t * new_device = kmalloc(sizeof(device_t));
	new_device->read = read_handler;
	new_device->write = write_handler;
	
	device_map->add(device_map, dev_name, new_device);
}

device_t *device_get(char *device)
{
	unsigned long *temp;
	return (device_t *)device_map->get(device_map, device, temp);
}
