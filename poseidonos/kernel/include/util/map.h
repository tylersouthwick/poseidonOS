#ifndef UTIL_MAP_H
#define UTIL_MAP_H

/************************Structures************************************/
typedef struct
{
	char *key;
	char *value;
	void *next;
} map_node_t;

typedef void map_add(void *, char *, void *, int);
typedef char *map_get(void *, char *);
typedef int map_size(void *);

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
map_t *linked_list_map_create(void);
void linked_list_map_add(map_t *, char *, void *, int);
char *linked_list_map_get(map_t *, char *);
int linked_list_map_size(map_t *);
/**********************************************************************/

#endif

