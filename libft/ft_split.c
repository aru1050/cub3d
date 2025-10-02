/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:42:58 by athamilc          #+#    #+#             */
/*   Updated: 2024/12/06 14:54:46 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_extrac_words(const char *s, int start, char c)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = start;
	len = 0;
	j = 0;
	while (s[i + len] && s[i + len] != c)
	{
		len++;
	}
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
	{
		return (NULL);
	}
	while (j < len)
	{
		str[j] = s[i + j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

static int	ft_count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
		{
			i++;
		}
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
			{
				i++;
			}
		}
	}
	return (count);
}

static void	*ft_free(char **str)
{
	int		i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		len;
	int		start;

	i = 0;
	start = 0;
	len = ft_count_words(s, c);
	str = (char **) malloc((len + 1) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		while (s[start] && s[start] == c)
			start++;
		str[i] = ft_extrac_words(s, start, c);
		if (!str[i])
			return (ft_free(str));
		while (s[start] && s[start] != c)
			start++;
		i++;
	}
	str[i] = NULL;
	return (str);
}
