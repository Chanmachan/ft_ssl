#include "options.h"
#include <unistd.h>
#include <string.h>

int parse_options(int ac, char **av, t_options *opts) {
  for (int i = 2; i < ac; i++) {
    if (av[i][0] == '-'){
      if (strlen(av[i]) == 2) {
	switch (av[i][1]) {
	case 'p':
	  opts->p = true;
	  break;
	case 'q':
	  opts->q = true;
	  break;
	case 'r':
	  opts->r = true;
	  break;
	case 's':
	  opts->s = true;
	  break;
	default:
	  print_err(ERR_INVALID_OPTION, av[i]);
	  return -1;
	}
      } else {
	print_err(ERR_INVALID_OPTION, av[i]);
	return -1;
      }
    } else {
      return i;
    }
  }
  return ac;
}
