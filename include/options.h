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

bool parse_options(int ac, char **av, t_options *opts);

#endif
