#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.h"

linked_list_t* create_linked_list() {
  linked_list_t *list;
  list = malloc(sizeof(linked_list_t));
  memset(list, 0, sizeof(linked_list_t));
  return list;
}

linked_list_t* append_node(linked_list_t *list) {
  linked_list_t *new_node;
  new_node = malloc(sizeof(linked_list_t));
  memset(new_node, 0, sizeof(linked_list_t));
  list->next = new_node;
  new_node->prev = list;
}

void delete_linked_list(linked_list_t *list) {
  if (!list) {
    return;
  }

  linked_list_t *next;
  next = *list->next;

  free(list);

  delete_linked_list(next);
}
