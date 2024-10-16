#ifndef ERROR_H
#define ERROR_H

#include <unistd.h>

typedef enum e_error_code{
  ERR_NO_ARGUMENTS,
  ERR_INVALID_COMMAND,
} t_error_code;

static const char* ERROR_MESSAGE[] = {
  "usage: ft_ssl command [flags] [file/string]\n",
  "ft_ssl: Error:'foobar' is an invalid command.\n\nCommands:\nmd5\nsha256\n\nFlags:\n-p -q -r -s\n"
};

void print_err(t_error_code code) {
  write(STDERR_FILENO, ERROR_MESSAGE[code], strlen(ERROR_MESSAGE[code]));
}

#endif
