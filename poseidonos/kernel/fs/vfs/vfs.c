/*************************************
 * vfs.c
 *
 * manages vfs stuff
 * *********************************/
#include <kernel.h>
#include <ktypes.h>

#include <util/map.h>

#include <vfs.h>
#include <fat.h>

map_t *filesystems;
extern map_t *mounts;

void vfs_register_fs(char *filesystem, void *mount_fs)
{
	filesystems->add(filesystems, filesystem, mount_fs);
}

void vfs_init()
{
	filesystems = linked_list_map_create();
	mounts = linked_list_map_create();

	fat_init();
}
