#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

linked_list_t* tokenize(char *input) {
   linked_list_t *list;
   
   list = create_linked_list();

   int i;
   for (i=0; i < strlen(input); i++) {
      printf("%c\n", input[i]);
   }

   return list;
}
