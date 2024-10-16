#include <stdio.h>
#include <string.h>

#include "error.h"

int main(int ac, char **av) {
  (void)ac;
  (void)av;
  if (ac < 2) {
    print_err(ERR_NO_ARGUMENTS, NULL);
    return 1;
  } else if (strcmp(av[1], "md5") != 0 && strcmp(av[1], "sha256") != 0) {
    print_err(ERR_INVALID_COMMAND, av[1]);
    return 1;
  }
  printf("Hello, World!\n");
  return 0;
}
