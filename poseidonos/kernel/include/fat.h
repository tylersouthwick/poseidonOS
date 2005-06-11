#ifndef FS_FAT_H
#define FS_FAT_H

/****************************************Includes*****************************/
#include <vfs.h>
/*****************************************************************************/

/****************************************Constants*****************************/
#define FAT_ATTR_NONE		0 /* no attribute bits */
#define FAT_ATTR_READ_ONLY	1  /* read-only */
#define FAT_ATTR_HIDDEN		2  /* hidden */
#define FAT_ATTR_SYSTEM		4  /* system */
#define FAT_ATTR_VOLUME_ID	8  /* volume label */
#define FAT_ATTR_DIRECTORY	16 /* directory */
#define FAT_ATTR_ARCHIVE	32 /* archived */
#define FAT_ATTR_LONG_NAME	(FAT_ATTR_READ_ONLY | FAT_ATTR_HIDDEN | FAT_ATTR_SYSTEM | FAT_ATTR_VOLUME_ID)

#define FAT_NAME_MAXLEN	8
#define FAT_LONGNAME_MAXLEN	256
#define	FAT_EXT_MAXLEN	3

#define FAT_FLAG_DELETED	(229 /*0xe5*/)
#define FAT_FLAG_EMPTY		0

#define FAT_SIZEOF			4096
/*****************************************************************************/

#define FAT_IS_READ_ONLY(a) ((a) & FAT_ATTR_READ_ONLY)
#define FAT_IS_HIDDEN(a)	((a) & FAT_ATTR_HIDDEN)
#define FAT_IS_SYSTEM(a)	((a) & FAT_ATTR_SYSTEM)
#define FAT_IS_VOLUME_ID(a)	((a) & FAT_ATTR_VOLUME_ID)
#define FAT_IS_DIRECTORY(a)	((a) & FAT_ATTR_DIRECTORY)
#define FAT_IS_ARCHIVE(a)	((a) & FAT_ATTR_ARCHIVE)
#define FAT_IS_LONG_NAME(a)	(a == 0xf)
#define FAT_IS_DELETED(a)		(0)
			//	a[0] == FAT_FLAG_DELETED)

//(FAT_IS_READ_ONLY(a) & FAT_IS_HIDDEN(a) & FAT_IS_SYSTEM(a) & FAT_IS_VOLUME_ID(a))

typedef struct fat_info {
	unsigned char jmpBoot[3];
	unsigned char OEMName[8];
	unsigned short BytsPerSec;
	unsigned char SecPerClus;
	unsigned short RsvdSecCnt;
	unsigned char NumFATs;
	unsigned short RootEntCnt;
	unsigned short TotSec16;
	unsigned char Media;
	unsigned short FATSz16;
	unsigned short SecPerTrk;
	unsigned short NumHeads;
	unsigned int HiddSec;
	unsigned int TotSec32;
	unsigned char DrvNum;
	unsigned char Reserved1;
	unsigned char BootSig;
	unsigned int VolID;
	unsigned char VolLab[11];
	unsigned char FilSysType[8];
} __attribute__ ((packed)) fat_info;

typedef struct fat_entry {
	unsigned char name[FAT_NAME_MAXLEN];
	unsigned char ext[FAT_EXT_MAXLEN];
	unsigned char attr;
	unsigned char NTRes;
	unsigned char CrtTimeTenth;
#ifdef FAT_USE_BITFIELDS_IN_STRUCT
	struct CrtTime
	{
		unsigned short sec:5;
		unsigned short min:6;
		unsigned short hour:5;
	};
	struct CrtDate
	{
		unsigned short day:5;
		unsigned short month:4;
		unsigned short:7;
	};
#else
	unsigned short CrtTime;
	unsigned short CrtDate;
#endif
	unsigned short LstAccDate;
	unsigned short FstClusHI;
	unsigned short WrtTime;
	unsigned short WrtDate;
	unsigned short FstClusLO;
	unsigned int FileSize;
} __attribute__ ((packed)) fat_entry;

typedef struct FAT {
	unsigned short int *table;
	unsigned int index;
} FAT;

int fat_mount(vfs_mount *);
void fat_umount(vfs_mount *);
vfs_entry *fat_ls(vfs_mount *, char *, int *);
vfs_entry *fat_do_ls(vfs_mount *, int, int, int *);

void fat_get_first_sector(vfs_mount *, char *, int *, int *, int *);
int fat_get_next_sector(vfs_mount *, int);

void fat_init(void);
FILE *fat_fopen(vfs_mount *, char *, char *);
void fat_fclose(vfs_mount *, FILE *);
FILE *fat_file_create(vfs_mount *, char *);
int fat_file_remove(vfs_mount *, char *);
int fat_file_write(vfs_mount *, char *, char *);
int fat_file_read(vfs_mount *, char *, char *);
char fat_getchar(vfs_mount *, FILE *);

#endif

