#ifndef ERROR_H
#define ERROR_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>

// characters fixed length
// 83+nul
#define ERR_MSG_LEN_INVALID_COMMAND 84
// 36+1
#define ERR_MSG_LEN_INVALID_OPTION 37

typedef enum e_error_code{
  ERR_NO_ARGUMENTS,
  ERR_INVALID_COMMAND,
  ERR_INVALID_OPTION,
  SUCCESS,
} t_error_code;

static const char* ERROR_MESSAGE[] = {
  "usage: ft_ssl command [flags] [file/string]\n",
  "ft_ssl: Error: '%s' is an invalid command.\n\nCommands:\nmd5\nsha256\n\nFlags:\n-p -q -r -s\n",
  "ft_ssl: Error: invalid option -- '%s'\n",
};

void print_err(t_error_code code, char *detail);

#endif
