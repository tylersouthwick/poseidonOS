#ifndef UTIL_MAP_H
#define UTIL_MAP_H

/************************Structures************************************/
typedef struct
{
	char *key;
	char *value;
	void *next;
} map_node_t;

typedef void map_add(void *map, char *key, void *value, int sizeOfValue);
typedef char *map_get(void *map, char *key);
typedef int map_size(void *map);

typedef struct map_t
{
	int count;
	map_node_t *first_node;
	map_add *add;
	map_get *get;
	map_size *size;
} map_t;
/**********************************************************************/

/*****************************prototypes*******************************/

//LinkedList Map
map_t *linked_list_map_create();
void linked_list_map_add(map_t *map, char *key, void *value, int size_of_value);
char *linked_list_map_get(map_t *map, char *key);
int linked_list_map_size(map_t *map);
/**********************************************************************/

#endif

