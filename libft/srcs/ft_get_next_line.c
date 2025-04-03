//
// Created by chanma on 2024/10/19.
//

#include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

static size_t	gnl_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static size_t	gnl_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	len_src;

	i = 0;
	len_src = gnl_strlen(src);
	if (n == 0)
		return (len_src);
	while (i < n - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len_src);
}

static size_t	gnl_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	if (size == 0)
		return (0);
	len_dst = gnl_strlen(dst);
	len_src = gnl_strlen(src);
	i = 0;
	if (size < len_dst)
		return (size + len_src);
	if (size > len_dst)
	{
		while (dst[i] != '\0')
			i++;
		dst = dst + i;
		i = 0;
		while (i < size - len_dst - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len_dst + len_src);
}

static char	*gnl_strjoin(char *s1, char *s2)
{
	char	*rtn_str;
	size_t	len_rtn_str;

	len_rtn_str = gnl_strlen(s1) + gnl_strlen(s2);
	rtn_str = (char *) malloc (sizeof(char) * (len_rtn_str + 1));
	if (rtn_str == NULL)
		return (NULL);
	gnl_strlcpy(rtn_str, s1, gnl_strlen(s1) + 1);
	gnl_strlcat(rtn_str, s2, len_rtn_str + 1);
	free(s1);
	return (rtn_str);
}

static char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*rtn_str;
	size_t	len_s;

	if (s == NULL)
		return (NULL);
	len_s = gnl_strlen(s);
	if (len_s < start)
		return (gnl_substr("", 0, 1));
	if (len > len_s - start)
		len = len_s - start;
	rtn_str = (char *) malloc (sizeof(char) * (len + 1));
	if (rtn_str == NULL)
		return (NULL);
	gnl_strlcpy(rtn_str, &s[start], len + 1);
	return (rtn_str);
}

static char	*gnl_strchr(char *s, int c)
{
	char	*new_s;
	size_t	i;

	new_s = (char *) s;
	i = 0;
	if (!s)
		return (NULL);
	while (new_s[i] != '\0')
	{
		if (new_s[i] == (char) c)
			return (new_s + i);
		i++;
	}
	if ((char) c == '\0')
		return (new_s + i);
	return (NULL);
}

static char	*read_lines(char *str, int fd)
{
	char		*buf;
	ssize_t		rd_bytes;

	rd_bytes = 1;
	buf = (char *) malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	while (rd_bytes != 0 && !gnl_strchr(str, '\n'))
	{
		rd_bytes = read(fd, buf, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[rd_bytes] = '\0';
		str = gnl_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

static char	*get_one_line(char *str)
{
	size_t	i;
	char	*rtn_str;

	if (str[0] == '\0')
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	rtn_str = gnl_substr(str, 0, i);
	if (rtn_str == NULL)
		return (NULL);
	return (rtn_str);
}

//str[0] == '\0' if empty

static char	*delete_last_line(char *str)
{
	size_t	i;
	char	*new_str;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	if (str[i] == '\n')
		i++;
	new_str = gnl_substr(&str[i], 0, gnl_strlen(&str[i]));
	if (new_str == NULL)
	{
		free(str);
		return (NULL);
	}
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*rtn_str;
	char		*tmp;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	tmp = str;
	str = read_lines(str, fd);
	if (!str)
	{
		free(tmp);
		return (NULL);
	}
	rtn_str = get_one_line(str);
	str = delete_last_line(str);
	return (rtn_str);
}

//#include <fcntl.h> // For O_RDONLY
//#include <unistd.h> // For close
//#include <stdio.h> // For printf
//#include <stdlib.h>
//
//int main(void)
//{
//	char 	*str;
//	int 	fd;
//	size_t 	i;
//
//	i = 0;
//	fd = open("example.txt", O_RDONLY);
//	while (1)
//	{
//		str = get_next_line(fd);
//		printf("[%zu] : %s\n-------------\n", i, str);
//		printf("%s", str);
//		if (str == NULL)
//		{
//			free(str);
//			break;
//		}
//		free(str);
//		i++;
//	}
//	close(fd);
//	return (0);
//}