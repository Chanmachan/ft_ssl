#include <stdio.h>
#include "options.h"
#include "ft_ssl.h"

int main(int ac, char **av) {
  if (ac < 2) {
    print_err(ERR_NO_ARGUMENTS, NULL);
    return 1;
  } else if (strcmp(av[1], "md5") != 0 && strcmp(av[1], "sha256") != 0) {
    print_err(ERR_INVALID_COMMAND, av[1]);
    return 1;
  }
  
  // optionがついてるか、ついてるなら処理
  t_options opts = {false, false, false, false};
  if (parse_options(ac, av, &opts)) {
    return 1;
  }
  printf("Options:\n");
  printf("  -p: %s\n", opts.p ? "true" : "false");
  printf("  -q: %s\n", opts.q ? "true" : "false");
  printf("  -r: %s\n", opts.r ? "true" : "false");
  printf("  -s: %s\n", opts.s ? "true" : "false");
  // 標準入力から値を受け取る処理
  
  printf("Hello, World!\n");
  return 0;
}
