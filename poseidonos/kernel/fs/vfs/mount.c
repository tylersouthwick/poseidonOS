#include <ktypes.h>
#include <kutil.h>
#include <kdebug.h>

#include <fat.h>
#include <kmalloc.h>
#include <string.h>
#include <screen.h>

extern map_t *filesystems;
map_t *mounts;

///this is assumed to be at fd0
int mount(char *dev, char *path, char *type) {
	long fs_mount;
	int (*__fs_mount)(vfs_mount *);
	unsigned long status = filesystems->get(filesystems, type, &fs_mount);
	vfs_mount *vmount;

	if (status < 0) {
		return -1;
	}

	vmount = kmalloc(sizeof(vfs_mount));
	vmount->device = device_get(dev);

	__fs_mount = (void *)status;
	status = __fs_mount(vmount);

	if (status < 0) {
		return -1;
	}

	mounts->add(mounts, path, vmount);

	return status;
}

void vfs_mount_parse(char *path, char *new_path, vfs_mount *vmount) {
	int len = strlen(path);

	strcpy(new_path, path);

	for (; len >= 0; len--) {
		if (len == strlen(path) || (len > 0 && new_path[len - 1] == '/') || (len == 0)) {
			if (mounts->contains(mounts, new_path) == true) {
				vfs_mount vmount2;
				mounts->get(mounts, new_path, &vmount2);
				kprint("found mount structure!\n");
	kprint("vmount2.fopen: ");
	put_int((int)(&(vmount2.fopen)), 0x10);
	kprint("\n");
		vmount2.fopen(2,5,5);
		fat_fopen(2,5,5);
				memcpy(vmount, &vmount2, sizeof(vfs_mount));
				return;
			}
			new_path[len] = 0;
		}
	}
	kprint("error! didn't find mount\n");
}

void umount_all() {
}


