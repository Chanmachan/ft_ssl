#ifndef ERROR_H
#define ERROR_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>

// 84 characters fixed length
// 83+nul
#define DEFAULT_MSG_LEN 84

typedef enum e_error_code{
  ERR_NO_ARGUMENTS,
  ERR_INVALID_COMMAND,
} t_error_code;

static const char* ERROR_MESSAGE[] = {
  "usage: ft_ssl command [flags] [file/string]\n",
  "ft_ssl: Error: '%s' is an invalid command.\n\nCommands:\nmd5\nsha256\n\nFlags:\n-p -q -r -s\n"
};

void print_err(t_error_code code, char *detail) {
  if (code == ERR_NO_ARGUMENTS) {
    write(STDERR_FILENO, ERROR_MESSAGE[code], strlen(ERROR_MESSAGE[code]));
  } else {
    size_t size = DEFAULT_MSG_LEN + strlen(detail);
    char buffer[size];
    snprintf(buffer, size, ERROR_MESSAGE[code], detail);
    write(STDERR_FILENO, buffer, strlen(buffer));
  }
}

#endif
