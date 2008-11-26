#include <ktypes.h>
#include <kdebug.h>

#include <screen.h>
#include <kmalloc.h>
#include <string.h>

#include <devices/floppy.h>

#include <fat.h>

static fat_info *fat_data;
static int FATSz;
static int fat_root_sector_start;
static int fat_root_sector_count;
//static FAT fat;

unsigned inline static int fat_cluster_to_sector(unsigned int cluster_num) {
	int root_dir_sectors = ((fat_data->BytsPerSec - 1) + (fat_data->RootEntCnt * 32)) / (fat_data->BytsPerSec);
	int fat_sectors = fat_data->NumFATs * fat_data->FATSz16;
	int data_start = fat_data->RsvdSecCnt + fat_sectors+ root_dir_sectors;
	int sector = data_start + ((cluster_num - 2) * fat_data->SecPerClus);

	return sector;
}

unsigned inline static int sector_to_fat_cluster(unsigned int sector) {
	int root_dir_sectors = ((fat_data->BytsPerSec - 1) + (fat_data->RootEntCnt * 32)) / (fat_data->BytsPerSec);
	int fat_sectors = fat_data->NumFATs * fat_data->FATSz16;
	int data_start = fat_data->RsvdSecCnt + fat_sectors+ root_dir_sectors;

	int cluster = ((sector - data_start) / (fat_data->SecPerClus)) + 2;

	return cluster;
}

void fat_init() {
	vfs_register_fs("fat", &fat_mount);
}

void fat_get_first_sector(vfs_mount *vmount, char *origPath, int *sector_start, int *sector_count, int *directory) {
	int token_count=0;
	int i;
	int h;
	char *temp_path;
	char *buffer;
	vfs_entry *entries;
	int item_count;
	int g;
	int len;
	char path[strlen(origPath) + 1];

	strcpy(path, origPath);
		
	*sector_count = fat_root_sector_count;
	*sector_start = fat_root_sector_start;

	///if we're only looking for root, then we don't need to do any more
	if (strcmp(path, "/")) {
		return;
	}
	
	///clean off the trailing '/' if there is one
	//if (path[strlen(path)] == '/')
	//	path[strlen(path)] == 0;

	///if it isn't the root, then let's follow the fat tree
	//find the first directory
	len = strlen(path);
	for (i=0; i < len; i++) {
		if (path[i] == '/') {
			path[i] = 0;
			token_count++;
		}
	}

	//temp_path = kmalloc(sizeof(char) * strlen(path));
	//strcpy(temp_path, path);
	temp_path = path;
	buffer = path;

	g=0;
	for (h=token_count; h > 0; h--) {
		char *dir_name;
		int found = 0;

		while(path[g] != 0)	{
			g++;
		}

		g++;
		dir_name = &path[g];
		entries = fat_do_ls(vmount, *sector_start, *sector_count, &item_count);

		for(i=0; i<item_count; i++) {
			if (strcmp(entries[i].name, dir_name)) {
				if (FAT_IS_DIRECTORY(entries[i].attributes)) {
					*directory = 1;
				} else {
					*directory = 0;
				}

				found = 1;
				*sector_start = fat_cluster_to_sector(entries[i].inode->inode_number);
				break;
			}
		}

		if (found) {
			return;
		} else {
			*sector_start = -1;
			return;
		}
	}
}

/*******************************************************************************
 * vfs_entry *fat_ls(char *path, int *item_count)
 * 
 * This returns a directory listing of a given path.
 * 
 * Parameters:
 * 	1) char *path
 * 		The path (relative to the root directory of the device)
 * 	2) int *item_count
 * 		This will contain the number of items in the directory
 * 
 * Return value:
 * 	A vfs_entry array where the number of elements is designated by item_count
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	January 3, 2005
 * *****************************************************************************/
vfs_entry *fat_ls(vfs_mount *vmount, char *path, int *item_count) {
	int sector_count;
	int sector_start;
	vfs_entry *entries;
	int isDirectory;
		
	fat_get_first_sector(vmount, path, &sector_start, &sector_count, &isDirectory);

	if (sector_start < 0) {
		*item_count = 0;
		return (vfs_entry *)0;
	}

	if (isDirectory) {
		/*do normal ls*/
		entries = fat_do_ls(vmount, sector_start, sector_count, item_count);
		return entries;
	} else {
		/*if it is really a file, then ls the directory
		 * and extract just the file*/
		char *dir;
		char *fname;
		int i;
		vfs_entry *single_entry;

		entries = 0;

		/*find just the name of the file*/
		dir = kmalloc(strlen(path)+1);
		strcpy(dir, path);

		for (i=strlen(dir)-1; i>=0; i--) {
			if (dir[i] == '/') {
				fname = kmalloc(strlen(dir) - i + 2);
				strcpy(fname, (char *)((int)&dir[i] + 1));
				dir[i+1] = 0;
				break;
			}
		}

		fat_get_first_sector(vmount, dir, &sector_start, &sector_count, &isDirectory);
		entries = fat_do_ls(vmount, sector_start, sector_count, item_count);

		for (i=0; i< *item_count; i++) {
			if (strcmp(entries[i].name, fname)) {
				single_entry = kmalloc(sizeof(vfs_entry));
				memcpy(single_entry, (void *)((int)entries + i*sizeof(vfs_entry)), sizeof(vfs_entry));
				kfree(entries);
				kfree(dir);
				kfree(fname);
				*item_count = 1;
				return single_entry;
			}
		}

		kfree(dir);
		kfree(fname);
	}

	/*if the file wasn't found (which shouldn't happen), just return 0*/
	*item_count = 0;
	kfree(entries);
	return (vfs_entry *)0;
}

vfs_entry *fat_do_ls(vfs_mount *vmount, int sector_start, int sector_count, int *item_count) {
	fat_entry *fat_entries;
	vfs_entry *vfs_entries;
	int i=0;
	char *read_buffer;
	int fat_counter;
	
	read_buffer = kmalloc(512 * sector_count);
	floppy_block_read(sector_start, read_buffer, 1);
	
	fat_entries = (fat_entry*)(read_buffer);

	*item_count = 0;
	i = 0;

	while (fat_entries[i].name[0] != FAT_FLAG_EMPTY) {
		if (fat_entries[i].name[0] == FAT_FLAG_DELETED) {
			i++;
			continue;
		}

		/// we don't want volume id files or files that have been deleted
		if (!FAT_IS_LONG_NAME(fat_entries[i].attr)) {
			(*item_count)++;
		}
		i++;
	}

	vfs_entries = kmalloc(sizeof(vfs_entry) * (*item_count));

	///add the fat entries to a vfs structure (array)
	fat_counter = 0;
	for (i=0; i < *item_count; i++) {
		//is fat_counter a valid index?
		while ((FAT_IS_LONG_NAME(fat_entries[fat_counter].attr)) || fat_entries[fat_counter].name[0] == FAT_FLAG_DELETED) {
			fat_counter++;
		}

		///build name
		memset(vfs_entries[i].name, 0, VFS_NAME_MAXLEN + 1);
		strip_whitespace(fat_entries[fat_counter].name, FAT_NAME_MAXLEN);
		memcpy(vfs_entries[i].name, fat_entries[fat_counter].name, FAT_NAME_MAXLEN);
		tolower(vfs_entries[i].name);

		///copy attributes,dates,times
		vfs_entries[i].attributes = fat_entries[fat_counter].attr;
		vfs_entries[i].create_date = fat_entries[fat_counter].CrtDate;
		vfs_entries[i].modified_date = fat_entries[fat_counter].WrtDate;
		vfs_entries[i].create_time = fat_entries[fat_counter].CrtTime;
		vfs_entries[i].modified_time = fat_entries[fat_counter].WrtTime;
		vfs_entries[i].size = fat_entries[fat_counter].FileSize;

		///setup the inode associated with the vfs entry
		///the inode number will be the fat cluster
		vfs_entries[i].inode = kmalloc(sizeof(struct vfs_inode));
		vfs_entries[i].inode->inode_number = (u64)fat_entries[fat_counter].FstClusLO;

		///clean up extension
		strip_whitespace(fat_entries[fat_counter].ext, FAT_EXT_MAXLEN);
		
		///add extension to valid files
		if ((!FAT_IS_DIRECTORY(vfs_entries[i].attributes)) && (fat_entries[fat_counter].ext[0] != 0)) {
			char *temp_name;
			temp_name = vfs_entries[i].name;
			tolower(fat_entries[fat_counter].ext);

			temp_name[strlen(temp_name)] = '.';
			memcpy((char *)((int)temp_name + strlen(temp_name)), fat_entries[fat_counter].ext, FAT_EXT_MAXLEN);
		}

		fat_counter++;
	}

	///clean up memory
	kfree(fat_entries);

	return vfs_entries;
}

int fat_get_next_sector(vfs_mount *vmount, int sector) {
	unsigned int fat_sector_number;
	unsigned int fat_offset;
	u16 next_cluster;
	u8 *fat_buffer;
	unsigned int cluster;

	cluster = sector_to_fat_cluster(sector);
	fat_offset = cluster + (cluster / 2);

	fat_sector_number = fat_data->RsvdSecCnt + (fat_offset / fat_data->BytsPerSec);
	fat_offset %= fat_data->BytsPerSec;

	/*we elliminate the need to do a boundary case check
	 * by reading in the 2 consecutive sectors*/
	fat_buffer = kmalloc(1024);
	floppy_block_read(fat_sector_number, fat_buffer, 2);
	
	next_cluster = *((u16 *) &fat_buffer[fat_offset]);

	if (cluster & 1) {
		next_cluster >>= 4;
	} else {
		next_cluster &= 0x0FFF;
	}

	kfree(fat_buffer);

	if (next_cluster > 0xFF8) {
		return -1;
	}

	if (next_cluster >=0x002 && next_cluster <= 0xFEF) {
		return fat_cluster_to_sector(next_cluster);
	}

	KLOG_DEBUG("fat_get_next_sector :: error!\n");
	return -1;
}

int fat_mount(vfs_mount *vmount) {
	unsigned char *read_buffer;
	
	read_buffer = (unsigned char *)kmalloc(512);
	
	///get the fat data
	vmount->device->read(0, read_buffer, 1);

	vmount->fopen = fat_fopen;

	///allocate data for the fat_data structure
	fat_data = kmalloc(sizeof(fat_info));
	memcpy(fat_data, read_buffer, sizeof(fat_info));
	kfree(read_buffer);
	
	///determine FATSz
	if (fat_data->FATSz16 != 0) {
		FATSz = fat_data->FATSz16;
	} else {
		FATSz = 0;
	}
		
	fat_root_sector_count = ((fat_data->RootEntCnt * 32) + (fat_data->BytsPerSec - 1)) / (fat_data->BytsPerSec);
	fat_root_sector_start = fat_data->RsvdSecCnt + (fat_data->NumFATs * FATSz);

	screen_set_color(SCREEN_FG_CYAN | SCREEN_BG_BLACK);
	KLOG_INFO("fd0: mounted as fat\n");
	screen_set_color(SCREEN_DEFAULT);

	KLOG_DEBUG("vmount: ");
	KLOG_INT_DEBUG((int)(&vmount), 0x10);
	KLOG_DEBUG("\n");

	KLOG_DEBUG("vmount.fopen: ");
	KLOG_INT_DEBUG((int)(&(vmount->fopen)), 0x10);
	KLOG_DEBUG("\n");

	return 1;
}

void fat_umount(vfs_mount * vmount) {
				/*
	kfree(fat_data);	
	if (fat.table != 0)
		kfree(fat.table);
		*/
}
