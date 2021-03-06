#include <ktypes.h>
#include <kutil.h>
#include <kdebug.h>

#include <fat.h>
#include <kmalloc.h>
#include <string.h>
#include <screen.h>

extern map_t *filesystems;
extern map_t *mounts;

///this is assumed to be at fd0
int mount(char *dev, char *path, char *type) {
	int (*__fs_mount)(vfs_mount *);
	unsigned long status;
	DEBUG_MSG(("mounting filesytstem of type: %s", type));
	__fs_mount = (void *)filesystems->get(filesystems, type);
	vfs_mount *vmount;

	if (status < 0) {
		return -1;
	}

	vmount = kmalloc(sizeof(vfs_mount));
	vmount->device = device_get(dev);

	status = __fs_mount(vmount);

	if (status < 0) {
		return -1;
	}

	mounts->add(mounts, path, (unsigned long)vmount);

	return status;
}

void vfs_mount_parse(char *path, char *new_path, vfs_mount *vmount) {
	int len = strlen(path);

	strcpy(new_path, path);

	for (; len >= 0; len--) {
		if (len == strlen(path) || (len > 0 && new_path[len - 1] == '/') || (len == 0)) {
			if (mounts->contains(mounts, new_path) == true) {
				vfs_mount *vmount2;
				vmount2 = (vfs_mount *)mounts->get(mounts, new_path);
				memcpy(vmount, vmount2, sizeof(vfs_mount));
				return;
			}
			new_path[len] = 0;
		}
	}
	ERROR_MSG(("error! didn't find mount"));
}

void umount_all() {
}


