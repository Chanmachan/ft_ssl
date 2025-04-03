#include "error.h"
#include "libft.h"

static const char *ERROR_MESSAGE[] = {
  "usage: ft_ssl command [flags] [file/string]\n",
  "ft_ssl: Error: '%s' is an invalid command.\n\nCommands:\nmd5\nsha256\n\nFlags:\n-p -q -r -s\n",
  "ft_ssl: Error: invalid option -- '%s'\n",
  "Error: while read: %s\n",
  "Error: while open: %s\n",
  "Error: memory allocation\n",
  "Error: -s option requires a string argument\n",
};

static char *format_error_message(const char *template, const char *detail) {
  char *result;
  size_t template_len = ft_strlen(template);
  size_t detail_len = detail ? ft_strlen(detail) : 0;

  // %s の数をカウント
  int placeholder_count = 0;
  for (size_t i = 0; template[i]; i++) {
    if (template[i] == '%' && template[i + 1] == 's') {
      placeholder_count++;
    }
  }

  // 置換後の長さを計算
  size_t result_len = template_len - (placeholder_count * 2) + (placeholder_count * detail_len) + 1;

  // バッファを確保
  result = (char *)malloc(result_len);
  if (!result) return NULL;

  // フォーマット処理
  result[0] = '\0';
  size_t i = 0;
  size_t current_pos = 0;
  while (i < template_len) {
    if (template[i] == '%' && template[i + 1] == 's' && detail) {
      ft_strlcat(result, detail, result_len);
      current_pos += detail_len;
      i += 2; // %s をスキップ
    } else {
      // 一文字ずつ追加
      result[current_pos] = template[i];
      result[current_pos + 1] = '\0';
      current_pos++;
      i++;
    }
  }

  return result;
}

void print_err(t_error_code code, const char *detail) {
  // エラーコードが範囲内かチェック
  if (code < 0 || code >= SUCCESS) {
    return;
  }

  const char *template = ERROR_MESSAGE[code];

  // プレースホルダー(%s)がないケース
  if (!detail || ft_strlen(template) == 0 || !ft_strnstr(template, "%s", ft_strlen(template))) {
    write(STDERR_FILENO, template, ft_strlen(template));
    return;
  }

  // フォーマット処理
  char *formatted = format_error_message(template, detail);
  if (!formatted) {
    // フォーマット失敗時は元のテンプレートを表示
    write(STDERR_FILENO, template, ft_strlen(template));
    return;
  }

  // エラーメッセージを出力
  write(STDERR_FILENO, formatted, ft_strlen(formatted));

  // メモリ解放
  free(formatted);
}
