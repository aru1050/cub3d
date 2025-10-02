/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:01:30 by athamilc          #+#    #+#             */
/*   Updated: 2024/12/02 12:34:17 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (((char )c) == 0)
	{
		while (s[i] != '\0')
		{
			i++;
		}
		return (&((char *)s)[i]);
	}
	while (s[i] != '\0')
	{
		if (((unsigned char *)s)[i] == ((unsigned char) c))
		{
			return (&((char *)s)[i]);
		}
		i++;
	}
	return (NULL);
}
