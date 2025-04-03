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
    char *filename;
    struct s_data *next;
} t_data;

void append_data(t_data **head, t_input_type input_type, char *input, char *filename);
void free_data_list(t_data *head);

#endif
