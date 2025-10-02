/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:36:01 by athamilc          #+#    #+#             */
/*   Updated: 2024/12/06 11:12:11 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned char	i;
	unsigned char	j;

	i = 0;
	if (little[0] == 0)
	{
		return (((char *)big));
	}
	while (((char *)big)[i] != '\0' && i < len)
	{
		j = 0;
		while (((char *)little)[j] == ((char *)big)[i + j] && i + j < len)
		{
			j++;
			if (((char *)little)[j] == 0)
			{
				return (&((char *)big)[i]);
			}
		}
		i++;
	}
	return (NULL);
}
