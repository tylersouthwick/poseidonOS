#ifndef H_VFS
#define H_VFS

#define VFS_NAME_MAXLEN 256

#define VFS_ATTR_NONE		0 /* no attribute bits */
#define VFS_ATTR_READ_ONLY	1  /* read-only */
#define VFS_ATTR_HIDDEN		2  /* hidden */
#define VFS_ATTR_SYSTEM		4  /* system */
#define VFS_ATTR_VOLUME_ID	8  /* volume label */
#define VFS_ATTR_DIRECTORY	16 /* directory */
#define VFS_ATTR_ARCHIVE	32 /* archived */
#define VFS_ATTR_LONG_NAME	(VFS_ATTR_READ_ONLY | VFS_ATTR_HIDDEN | VFS_ATTR_SYSTEM | VFS_ATTR_VOLUME_ID)

#define VFS_IS_READ_ONLY(a) (a & VFS_ATTR_READ_ONLY)
#define VFS_IS_HIDDEN(a)	(a & VFS_ATTR_HIDDEN)
#define VFS_IS_SYSTEM(a)	(a & VFS_ATTR_SYSTEM)
#define VFS_IS_VOLUME_ID(a)	(a & VFS_ATTR_VOLUME_ID)
#define VFS_IS_DIRECTORY(a)	(a & VFS_ATTR_DIRECTORY)
#define VFS_IS_ARCHIVE(a)	(a & VFS_ATTR_ARCHIVE)
#define VFS_IS_LONG_NAME(a)	(a & VFS_ATTR_LONG_NAME)

typedef struct vfs_entry
{
	unsigned char name[VFS_NAME_MAXLEN+1];
	unsigned int attributes;
	unsigned int mode;
	unsigned int date;
	unsigned int data;
} vfs_entry;

#endif
