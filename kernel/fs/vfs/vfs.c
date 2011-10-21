/*************************************
 * vfs.c
 *
 * manages vfs stuff
 * *********************************/
#include <ktypes.h>
#include <kdebug.h>

#include <util/map.h>

#include <vfs.h>
#include <fat.h>
#include <kmalloc.h>

map_t *filesystems;
map_t *mounts;
file_handles_t *file_handles;

void vfs_register_fs(char *filesystem, void *mount_fs) {
	filesystems->add(filesystems, filesystem, (unsigned long)mount_fs);
}

void vfs_init() {
	DEBUG_MSG(("Setting up VFS"));
	filesystems = linked_list_map_create();
	mounts = linked_list_map_create();

	file_handles = kmalloc(sizeof(file_handles_t) * VFS_FILE_HANDLES);

	fat_init();

	DEBUG_MSG(("Setting up VFS"));
}
