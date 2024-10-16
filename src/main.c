#include <stdio.h>
#include <string.h>

#include "error.h"

int main(int ac, char **av) {
  (void)ac;
  (void)av;
  if (ac < 2) {
    print_err(ERR_NO_ARGUMENTS);
    return 1;
  } else if (strcmp(av[1], "md5") || strcmp(av[1], "sha256")) {
    print_err(ERR_INVALID_COMMAND);
    return 1;
  }
  printf("Hello, World!\n");
  return 0;
}
