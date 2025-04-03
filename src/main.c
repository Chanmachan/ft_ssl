#include <stdio.h>
#include "options.h"
#include "ft_ssl.h"
#include "libft.h"
#include <fcntl.h>

#define BUFFER_SIZE 1024

char *read_content(int fd, const char *error_source) {
  char buffer[BUFFER_SIZE];
  ssize_t bytes_read;
  char *content = NULL;
  size_t content_len = 0;
  char *tmp;

  // コンテンツの初期化
  content = ft_strdup("");
  if (content == NULL) {
    print_err(ERR_MEMORY_ALLOCATION, NULL);
    return NULL;
  }
  content_len = 0;

  // EOF まで読み込む
  while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
    buffer[bytes_read] = '\0'; // ヌル終端を保証

    // 既存のコンテンツと新しいバッファを結合
    tmp = content;
    content = (char *) malloc(content_len + bytes_read + 1);
    if (content == NULL) {
      free(tmp);
      print_err(ERR_MEMORY_ALLOCATION, NULL);
      return NULL;
    }

    ft_strlcpy(content, tmp, content_len + 1);
    ft_strlcat(content, buffer, content_len + bytes_read + 1);
    content_len += bytes_read;
    free(tmp);
  }

  if (bytes_read == -1) {
    free(content);
    print_err(ERR_READ, error_source);
    return NULL;
  }

  return content;
}

void read_from_stdin(t_data **data) {
  char *content = read_content(STDIN_FILENO, "stdin");

  if (content == NULL) {
    exit(EXIT_FAILURE);
  }

  append_data(data, INPUT_TYPE_STDIN, content, NULL);
}

void read_from_file(t_data **data, char *filename) {
  int fd = open(filename, O_RDONLY);
  if (fd < 0) {
    print_err(ERR_OPEN, filename);
    return;
  }

  char *content = read_content(fd, filename);
  close(fd);

  if (content == NULL) {
    return;
  }

  append_data(data, INPUT_TYPE_FILE, content, filename);
}

void process_string_argument(t_data **data, char *str) {
  append_data(data, INPUT_TYPE_ARGUMENT, ft_strdup(str), NULL);
}

int main(int ac, char **av) {
  if (ac < 2) {
    print_err(ERR_NO_ARGUMENTS, NULL);
    return 1;
  }
  if (ft_strncmp(av[1], "md5", ft_strlen(av[1])) != 0 \
      && ft_strncmp(av[1], "sha256", ft_strlen(av[1])) != 0) {
    print_err(ERR_INVALID_COMMAND, av[1]);
    return 1;
  }

  // optionがついてるか、ついてるなら処理
  t_options opts = {false, false, false, false};
  int arg_index = parse_options(ac, av, &opts);
  if (arg_index == -1) {
    return 1;
  }
  printf("Options:\n");
  printf("  -p: %s\n", opts.p ? "true" : "false");
  printf("  -q: %s\n", opts.q ? "true" : "false");
  printf("  -r: %s\n", opts.r ? "true" : "false");
  printf("  -s: %s\n", opts.s ? "true" : "false");

  t_data *data = NULL;
  bool stdin_processed = false;

  if (opts.p) {
    read_from_stdin(&data);
    stdin_processed = true;
  }

  // 標準入力から値を受け取る処理
  if (opts.s) {
    if (arg_index < ac) {
      process_string_argument(&data, av[arg_index]);
      arg_index++;
    } else {
      print_err(ERR_MISSING_STRING_ARG, NULL);
      free_data_list(data);
      return 1;
    }
  }

  if (arg_index < ac) {
    for (int i = arg_index; i < ac; i++) {
      read_from_file(&data, av[i]);
    }
  } else if (!stdin_processed && !opts.s) {
    // 引数がなく、標準入力もまだ処理されていない場合は標準入力を読み込む
    read_from_stdin(&data);
  }

  // データの表示（デバッグ用）
  if (data != NULL) {
    t_data *current = data;
    int count = 0;
    while (current) {
      if (current->input_type == INPUT_TYPE_STDIN)
        printf("Data[%d] InputType: STDIN, ", count);
      else if (current->input_type == INPUT_TYPE_ARGUMENT)
        printf("Data[%d] InputType: ARGUMENT, ", count);
      else if (current->input_type == INPUT_TYPE_FILE)
        printf("Data[%d] InputType: FILE, ", count);

      if (current->input_type == INPUT_TYPE_FILE && current->filename)
        printf("filename: %s, ", current->filename);

      if (current->input) {
        size_t input_len = ft_strlen(current->input);
        printf("input length: %zu\n", input_len);

        // デバッグ用に入力内容の一部を表示
        if (input_len > 30) {
          char preview[31];
          ft_strlcpy(preview, current->input, 31);
          printf("Input preview: '%s...'\n", preview);
        } else {
          printf("Input: '%s'\n", current->input);
        }
      } else {
        printf("input: NULL\n");
      }

      current = current->next;
      count++;
    }
  } else {
    printf("data is NULL\n");
  }

  free_data_list(data);

  return 0;
}
