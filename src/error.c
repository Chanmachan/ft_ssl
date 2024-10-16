#include "error.h"

void print_err(t_error_code code, char *detail) {
  if (code == ERR_NO_ARGUMENTS) {
    write(STDERR_FILENO, ERROR_MESSAGE[code], strlen(ERROR_MESSAGE[code]));
  } else {
    size_t size = strlen(detail);
    switch (code) {
    case ERR_INVALID_COMMAND:
      size += ERR_MSG_LEN_INVALID_COMMAND;
      break;
    case ERR_INVALID_OPTION:
      size += ERR_MSG_LEN_INVALID_OPTION;
      break;
    default:
      return;
    }
    char buffer[size];
    snprintf(buffer, size, ERROR_MESSAGE[code], detail);
    write(STDERR_FILENO, buffer, strlen(buffer));
  }
}
