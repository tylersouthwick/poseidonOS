#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct {
  struct linked_list_t *prev;
  struct linked_list_t *next;
  char *data;
} linked_list_t;

linked_list_t* create_linked_list();

void delete_linked_list(linked_list_t *list);

linked_list_t* append_node(linked_list_t *list);

#endif
