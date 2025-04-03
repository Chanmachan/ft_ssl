#ifndef ERROR_H
#define ERROR_H

#include <unistd.h>

typedef enum e_error_code{
  ERR_NO_ARGUMENTS,
  ERR_INVALID_COMMAND,
  ERR_INVALID_OPTION,
  ERR_READ,
  ERR_OPEN,
  ERR_MEMORY_ALLOCATION,
  ERR_MISSING_STRING_ARG,
  SUCCESS,
} t_error_code;

#define MAX_ERROR_MSG_LEN 256

void print_err(t_error_code code, const char *detail);

#endif
