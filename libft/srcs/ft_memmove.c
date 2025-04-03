/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hommayunosuke <hommayunosuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 02:12:24 by hommayunosu       #+#    #+#             */
/*   Updated: 2023/01/27 02:12:25 by hommayunosu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*new_dest;
	unsigned char	*new_src;

	new_dest = (unsigned char *)dest;
	new_src = (unsigned char *)src;
	if (new_dest == new_src || n == 0)
		return (dest);
	if (dest > src)
	{
		while (n--)
			new_dest[n] = new_src[n];
	}
	else
		ft_memcpy(new_dest, new_src, n);
	return (dest);
}

/*#include <stdio.h>
#include <string.h>

int main()
{
	char	*str = NULL;

	ft_memmove(str + 1, str, 2);
	memmove(str + 1, str, 2);
	printf("%s\n", str);
}*/
