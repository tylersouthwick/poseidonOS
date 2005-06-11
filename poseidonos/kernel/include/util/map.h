#ifndef UTIL_MAP_H
#define UTIL_MAP_H

/************************Structures************************************/
typedef struct
{
	char *key;
	char *value;
	void *next;
} map_node_t;

typedef struct map_t
{
	int count;
	map_node_t *first_node;
	void (*add)(struct map_t *, char *, void *);
	int (*get)(struct map_t *, char *, void *);
	int (*size)(struct map_t *);
	bool (*contains)(struct map_t *, char *);
} map_t;
/**********************************************************************/

/*****************************prototypes*******************************/

//LinkedList Map
map_t *linked_list_map_create(void);
void linked_list_map_add(map_t *, char *, void *);
int linked_list_map_get(map_t *map, char *key, unsigned long *value);
bool linked_list_map_contains(map_t *map, char *key);
int linked_list_map_size(map_t *);
/**********************************************************************/

#endif

