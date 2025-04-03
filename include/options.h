#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>
#include "error.h"

typedef struct s_options {
  bool p;
  bool q;
  bool r;
  bool s;
} t_options;

// returns the index of the array after the option
int parse_options(int ac, char **av, t_options *opts);

#endif
