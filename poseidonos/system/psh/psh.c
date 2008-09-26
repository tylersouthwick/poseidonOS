#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "tokenizer.h"

int main(char *args) {
  char *inputStr;
  struct linked_list_t *tokens;

  inputStr = malloc(strlen(args) + 1);
  strcpy(inputStr, "this is a test");

  tokens = tokenize(inputStr);

  free(inputStr);
}
