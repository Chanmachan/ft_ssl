#ifndef FT_SSL_H
#define FT_SSL_H

typedef enum s_input_type {
    INPUT_TYPE_STDIN,
    INPUT_TYPE_ARGUMENT,
    INPUT_TYPE_FILE,
} t_input_type;

typedef struct s_data {
  t_input_type input_type;
  char *input;
  char *hash;
} t_data;

#endif
