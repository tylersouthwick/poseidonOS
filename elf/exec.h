#ifndef EXEC_H
#define EXEC_H

struct exec {
  int (*entry)(int argc, char **argv);
  char *data;
  void (*free)(struct exec *);
};

#endif
