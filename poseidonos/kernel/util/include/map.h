#ifndef UTIL_MAP_H
#define UTIL_MAP_H

/************************Structures************************************/
typedef struct
{
	char *key;
	char *value;
	void *next;
} MapNode;

typedef struct
{
	int count;
	MapNode *first_node;
} Map;
/**********************************************************************/

/*****************************prototypes*******************************/
Map *mapCreate();
void mapAdd(Map *map, char *key, char *value, int sizeOfValue);
char *mapGet(Map *map, char *key);
int mapSize(Map *map);
/**********************************************************************/

#endif

