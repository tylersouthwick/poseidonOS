#ifndef UTIL_HASHMAP_H
#define UTIL_HASHMAP_H

/************************Structures************************************/
typedef struct
{
	char *key;
	char *value;
	void *next;
} HashMapNode;

typedef struct
{
	int count;
	HashMapNode *node;
} HashMap;
/**********************************************************************/

/*****************************prototypes*******************************/
HashMap *newHashMap();
void addHashMapValue(HashMap *hashMap, char *key, char *value, int sizeOfValue);
char *getHashMapValue(HashMap *hashMap, char *key);
int getHashMapCount(HashMap *hashMap);
/**********************************************************************/

#endif

