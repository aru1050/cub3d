/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_config_and_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:06:22 by athamilc          #+#    #+#             */
/*   Updated: 2025/11/24 02:13:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_line(const char *s)
{
	int		i;
	int		has_symbol;
	char	c;

	if (!s)
		return (0);
	i = 0;
	has_symbol = 0;
	while (s[i] && s[i] != '\n')
	{
		c = s[i];
		if (c != ' ' && c != '0' && c != '1'
			&& c != 'N' && c != 'S' && c != 'E' && c != 'W')
			return (0);
		if (c == '0' || c == '1' || c == 'N'
			|| c == 'S' || c == 'E' || c == 'W')
			has_symbol = 1;
		i++;
	}
	return (has_symbol);
}

static int	is_blank_line(const char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		if (!ft_isspace((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	split_fill(char **lines, char **cfg, char **map)
{
	int	i;
	int	c;
	int	m;
	int	in_map;

	i = 0;
	c = 0;
	m = 0;
	in_map = 0;
	while (lines[i])
	{
		if (!in_map && is_map_line(lines[i]))
			in_map = 1;
		if (in_map)
			map[m++] = ft_strdup(lines[i]);
		else if (!is_blank_line(lines[i]))
			cfg[c++] = ft_strdup(lines[i]);
		i++;
	}
	cfg[c] = NULL;
	map[m] = NULL;
}

int	split_config_and_map(char **lines, char ***cfg_out, char ***map_out)
{
	char	**cfg;
	char	**map;
	int		count;

	count = 0;
	while (lines[count])
		count++;
	cfg = malloc(sizeof(char *) * (count + 1));
	map = malloc(sizeof(char *) * (count + 1));
	if (!cfg || !map)
		return (0);
	split_fill(lines, cfg, map);
	*cfg_out = cfg;
	*map_out = map;
	return (1);
}
