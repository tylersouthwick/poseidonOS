#ifndef H_VFS
#define H_VFS

#define VFS_NAME_MAXLEN 256

#define VFS_ATTR_NONE		0	/* no attribute bits */
#define VFS_ATTR_READ_ONLY	1	/* read-only */
#define VFS_ATTR_HIDDEN		2	/* hidden */
#define VFS_ATTR_SYSTEM		4	/* system */
#define VFS_ATTR_VOLUME_ID	8	/* volume label */
#define VFS_ATTR_DIRECTORY	16	/* directory */
#define VFS_ATTR_ARCHIVE	32	/* archived */
#define VFS_ATTR_LONG_NAME	(VFS_ATTR_READ_ONLY | VFS_ATTR_HIDDEN | VFS_ATTR_SYSTEM | VFS_ATTR_VOLUME_ID)

#define VFS_IS_READ_ONLY(a) (a & VFS_ATTR_READ_ONLY)
#define VFS_IS_HIDDEN(a)	(a & VFS_ATTR_HIDDEN)
#define VFS_IS_SYSTEM(a)	(a & VFS_ATTR_SYSTEM)
#define VFS_IS_VOLUME_ID(a)	(a & VFS_ATTR_VOLUME_ID)
#define VFS_IS_DIRECTORY(a)	(a & VFS_ATTR_DIRECTORY)
#define VFS_IS_ARCHIVE(a)	(a & VFS_ATTR_ARCHIVE)
#define VFS_IS_LONG_NAME(a)	(a & VFS_ATTR_LONG_NAME)

typedef struct FILE
{
	unsigned int offset;
	unsigned int size;
	unsigned char *data;
	struct vfs_inode *inode;
} FILE;

typedef int fpos_t;

typedef struct vfs_entry
{
	unsigned char name[VFS_NAME_MAXLEN+1];
	unsigned int attributes;
	unsigned int mode;
	unsigned short create_date;
	unsigned short modified_date;
	unsigned short create_time;
	unsigned short modified_time;
	unsigned int size;
	unsigned int data;
	struct vfs_inode * inode;
} vfs_entry;

typedef struct vfs_inode
{
	u64 inode_number;

	/*operations*/
	void (*create)(struct vfs_inode *, struct vfs_inode *, struct vfs_entry *);
	int (*mkdir)(struct vfs_inode *, struct vfs_entry *, int);
	int (*rmdir)(struct vfs_inode *, struct vfs_entry *);
	int (*rename)(struct vfs_inode *, struct vfs_entry *, struct vfs_entry *);
	FILE *(*read)(struct vfs_inode *);
	void (*write)(struct vfs_inode *, char *, int);
} vfs_inode;

typedef struct vfs_mount
{
	device_t *device;

	/*operations*/
	FILE *(*fopen)(struct vfs_mount *, char *, char *);
} vfs_mount;

typedef struct file_handles_t
{
	char *data;
} file_handles_t;

void vfs_register_fs(char *, void *);
void vfs_init(void);

/*mount prototypes*/
int mount(char *, char *, char *);
void vfs_mount_parse(char *path, char *new_path, vfs_mount *vmount);
int umount(char *);
void umount_all(void);
void mount_all(void);

/*ls prototypes*/
vfs_entry *ls(char *);

/*file prototypes*/
#define EOF -1


/*this is the default number of file handles available by the system
 * no more than this many files can be opened*/
#define VFS_FILE_HANDLES 255

#define SEEK_CUR 0
#define SEEK_END 1
#define SEEK_SET 2

int fclose(FILE *);
int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
int fgetc(FILE *);
int fgetpos(FILE *, fpos_t *);
char *gets(char *, int, FILE *);
FILE *fopen(char *, char *);
int fputc(int, FILE *);
int fputs(const char *, FILE *);
size_t fread(void *, size_t, size_t, FILE *);
int fseek(FILE *, long int, int);
long int ftell(FILE *);

#endif

