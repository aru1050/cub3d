/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:53:06 by athamilc          #+#    #+#             */
/*   Updated: 2024/12/06 09:43:44 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while (s1[i] == s2[i] && i < n - 1)
	{
		if (s1[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	return (((unsigned char *)s1)[i] - (((unsigned char *)s2)[i]));
}
/*
int	main()
{
	printf("%d",ft_strncmp("Hello","Hell0",0));
}*/
