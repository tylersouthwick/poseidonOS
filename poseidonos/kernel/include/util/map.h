#ifndef UTIL_MAP_H
#define UTIL_MAP_H

/************************Structures************************************/
typedef struct
{
	char *key;
	char *value;
	void *next;
} MapNode;

typedef map_add(struct Map *map, char *key, void *value, int sizeOfValue);
typedef map_get(struct Map *map, char *key);
typedef map_size(struct Map *map);

typedef struct Map
{
	int count;
	MapNode *first_node;
	map_add *add;
	map_get *get;
	map_size *size;
} Map;
/**********************************************************************/

/*****************************prototypes*******************************/

//LinkedList Map
Map *LinkedListMapCreate();
void LinkedListMapAdd(Map *map, char *key, void *value, int sizeOfValue);
char *LinkedListMapGet(Map *map, char *key);
int LinkedListMapSize(Map *map);
/**********************************************************************/

#endif

