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
Map *newMap();
void addMapValue(Map *map, char *key, char *value, int sizeOfValue);
char *getMapValue(Map *map, char *key);
int getMapCount(Map *map);
/**********************************************************************/

#endif

