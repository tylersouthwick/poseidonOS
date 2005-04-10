#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>
#include <kutil.h>

Map *mapCreate()
{
	Map *map;

	map = (Map *)kmalloc(sizeof(Map));
	map->first_node = (MapNode *)0;
	map->count = 0;

	return map;
}

void mapAdd(Map *map, char *key, void *value, int sizeOfValue)
{
	MapNode *tempNode;
	MapNode *newNode;

	tempNode = map->first_node;

	/*setup new node*/
	newNode = (MapNode *)kmalloc(sizeof(MapNode));
	newNode->key = (char *)kmalloc(strlen(key) + 1);
	strcpy(newNode->key, key);
	newNode->value = (char *)kmalloc(sizeOfValue);
	memcpy(newNode->value, value, sizeOfValue);
	newNode->next = 0;

	/*is this the first item in the list?*/
	if (tempNode == 0)
		/*add the new node*/
		map->first_node = newNode;
	else {
		/*find the last node in the list*/
		while (tempNode->next != 0)
			tempNode = (MapNode *)tempNode->next;

		/*add the new node*/
		tempNode->next = newNode;
	}

	map->count++;
}

char *mapGet(Map *map, char *key)
{
	MapNode *tempNode;

	tempNode = map->first_node;

	if (tempNode == 0)
		return (char *)-1;

	/*find the node that has the key*/
	while (tempNode && tempNode->key && strcmp(tempNode->key, key))
		tempNode = (MapNode *)tempNode->next;
	
	return tempNode->value;
}

int mapSize(Map *map)
{
	return map->count;
}

