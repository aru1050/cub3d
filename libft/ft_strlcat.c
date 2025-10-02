/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:14:10 by athamilc          #+#    #+#             */
/*   Updated: 2024/11/13 16:16:50 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	j = 0;
	while (dst[i] != '\0')
	{
		i++;
	}
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (siz <= dst_len)
		return (src_len + siz);
	while (src[j] != '\0' && i < siz - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (src_len + dst_len);
}
/*
#include <bsd/string.h>
int	main(void)
{
	char dest[] = "Hello";
	char src[] = "World";
	char dest_native[] = "Hello";
	char src_native[] = "World";

	printf("%zu\n", ft_strlcat(dest, src,3));
	printf("%zu\n", strlcat(dest_native, src_native,3));
	printf("%s\n",dest);
	printf("%s\n",dest_native);
}*/
