#include <ktypes.h>
#include <fat.h>
#include <floppy.h>
#include <screen.h>
#include <kmalloc.h>
#include <vfs.h>
#include <string.h>

fat_info *fat_data;
int FATSz;
int fat_root_sector_start;
int fat_root_sector_count;
vfs_entry *fat_do_ls(int sector_start, int sector_count, int *item_count);

void fat_get_sector(char *path, int *sector_start, int *sector_count)
{		
	int token_count=0;
	int i;
		int h;
		char *temp_path;
		char *buffer;
		vfs_entry *entries;
		int item_count;
		
	*sector_count = fat_root_sector_count;
	*sector_start = fat_root_sector_start;

	///if we're only looking for root, then we don't need to do any more
	if (strcmp(path, "/"))
		return;
	
	///if it isn't the root, then let's follow the fat tree
	//find the first directory
	kprint("finding path: ");
	kprint(path);
	kprint("\n");
		
	for (i=0; i < strlen(path); i++)
		if (path[i] == '/')
			token_count++;
				
	kprint("Directory count: ");
	put_int(token_count, 10);
	kprint("\n");

		
	temp_path = kmalloc(sizeof(char) * strlen(path));
	strcpy(temp_path, path);
	buffer = temp_path;
	/*	
	for (h=1; h < strlen(temp_path); h++)
	{
		if (path[h] == '/')
		{
			char *temp;
			
			temp_path[h] = 0;
			kprint("dir: ");
			temp = ((char *)(buffer+sizeof(char)));
			kprint(temp);
			kprint("...");
			entries = fat_do_ls(*sector_start, *sector_count, &item_count);
			while(entries!=0)
			{
				if (strcmp(entries->name, temp))
				{
					kprint("found!");
					kprint(" -> ");
					if (VFS_IS_DIRECTORY(entries->attributes))
					{
						kprint("<DIR>");
						break;
					}
				}
				entries = entries->next;
			}
			kprint("\n");
			buffer = temp_path + h;
			temp_path[h] = '/';
		}
	}
	///get the last token
	kprint("dir: ");
	kprint(((char *)(buffer+sizeof(char))));
	kprint("\n");

	*/
	
	return;
}

/*******************************************************************************
 * bool fat_ls(char *path, vfs_entry *entries, int *item_count)
 * 
 * This returns a directory listing of a given path.
 * 
 * Parameters:
 * 	1) char *path
 * 		The path (relative to the root directory of the device)
 * 	2) vfs_entry *entries
 * 		A pointer to a preallocated buffer
 * 	3) int *item_count
 * 		This will contain the number of items in the directory
 * 
 * Return value:
 * 	bool value that says if it completed the operation successfully or not
 * 
 * Author:	Tyler Southwick (northfuse@gmail.com)
 * Date:	January 3, 2005
 * *****************************************************************************/
vfs_entry *fat_ls(char *path, int *item_count)
{
	int sector_count;
	int sector_start;
	vfs_entry *entries;
		
	fat_get_sector(path, &sector_start, &sector_count);

	entries = fat_do_ls(sector_start, sector_count, item_count);

	return entries;
}

vfs_entry *fat_do_ls(int sector_start, int sector_count, int *item_count)
{
	fat_entry *fat_entries;
	vfs_entry *p_entries;
	vfs_entry *vfs_entries;
	int i=0;
	char *read_buffer;
	int fat_counter;
	int vfs_counter;
	
	read_buffer = kmalloc(512 * sector_count);
	floppy_block_read(sector_start, read_buffer, 1);
	
	fat_entries = (fat_entry*)(read_buffer);

	*item_count = 0;
	i = 0;
	while (fat_entries[i].name[0] != FAT_FLAG_EMPTY)
	{
		/// we don't want volume id files or files that have been deleted
		if (!FAT_IS_LONG_NAME(fat_entries[i].attr))
			(*item_count)++;
		i++;
	}

	vfs_entries = kmalloc(sizeof(vfs_entry) * (*item_count));

	///add the fat entries to a vfs structure (array)
	fat_counter = 0;
	for (i=0; i < *item_count; i++)
	{
		//is fat_counter a valid index?
		while (FAT_IS_LONG_NAME(fat_entries[fat_counter].attr))
				fat_counter++;

		///build name
		memset(vfs_entries[i].name, 0, VFS_NAME_MAXLEN + 1);
		strip_whitespace(fat_entries[fat_counter].name, FAT_NAME_MAXLEN);
		memcpy(vfs_entries[i].name, fat_entries[fat_counter].name, FAT_NAME_MAXLEN);
		tolower(vfs_entries[i].name);

		///copy attributes
		vfs_entries[i].attributes = fat_entries[fat_counter].attr;

		///clean up extension
		strip_whitespace(fat_entries[fat_counter].ext, FAT_EXT_MAXLEN);
		
		///add extension to valid files
		if ((!FAT_IS_DIRECTORY(vfs_entries[i].attributes)) && (fat_entries[fat_counter].ext[0] != 0))
		{
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

void fat_mount()
{
	unsigned char *read_buffer;
	
	read_buffer = (unsigned char *)kmalloc(512);
	
	/*get the fat data*/
	floppy_block_read(0, read_buffer, 1);
	fat_data = (fat_info *)read_buffer;
	
	///determine FATSz
	if (fat_data->FATSz16 != 0)
		FATSz = fat_data->FATSz16;
	else
		FATSz = 0;//fat_data->FATSz32;
		
		
	fat_root_sector_count = ((fat_data->RootEntCnt * 32) + (fat_data->BytsPerSec - 1)) / (fat_data->BytsPerSec);
	fat_root_sector_start = fat_data->RsvdSecCnt + (fat_data->NumFATs * FATSz);

	kprint("fd0: mounted as fat\n");
}

void fat_umount()
{
	kfree(fat_data);	
}
