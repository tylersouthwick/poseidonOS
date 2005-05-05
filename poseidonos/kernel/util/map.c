#include <kernel.h>
#include <ktypes.h>
#include <kdebug.h>
#include <kutil.h>

map_t *linked_list_map_create()
{
	map_t *map;

	map = (map_t *)kmalloc(sizeof(map_t));
	map->first_node = (map_node_t *)0;
	map->count = 0;

	/*setup function pointers*/
	map->add = &linked_list_map_add;
	map->get = &linked_list_map_get;
	map->size = &linked_list_map_size;

	return map;
}

void linked_list_map_add(map_t *map, char *key, void *value, int size_of_value)
{
	map_node_t *temp_node;
	map_node_t *new_node;

	temp_node = map->first_node;

	/*setup new node*/
	new_node = (map_node_t *)kmalloc(sizeof(map_node_t));
	new_node->key = (char *)kmalloc(strlen(key) + 1);
	strcpy(new_node->key, key);
	new_node->value = (char *)kmalloc(size_of_value);
	memcpy(new_node->value, value, size_of_value);
	new_node->next = 0;

	/*is this the first item in the list?*/
	if (temp_node == 0)
		/*add the new node*/
		map->first_node = new_node;
	else {
		/*find the last node in the list*/
		while (temp_node->next != 0)
			temp_node = (map_node_t *)temp_node->next;

		/*add the new node*/
		temp_node->next = new_node;
	}

	map->count++;
}

char *linked_list_map_get(map_t *map, char *key)
{
	map_node_t *temp_node;

	temp_node = map->first_node;

	if (temp_node == 0)
		return (char *)-1;

	/*find the node that has the key*/
	while (temp_node && temp_node->key && strcmp(temp_node->key, key))
		temp_node = (map_node_t *)temp_node->next;
	
	return temp_node->value;
}

int linked_list_map_size(map_t *map)
{
	return map->count;
}

