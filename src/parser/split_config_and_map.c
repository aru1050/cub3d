/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_config_and_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcalma <vcalma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:38:19 by vcalma            #+#    #+#             */
/*   Updated: 2025/10/20 15:38:20 by vcalma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_line(const char *s)
{
	int	i;
	int	has_symbol;

	if (!s)
		return (0);
	i = 0;
	has_symbol = 0;
	while (s[i] && s[i] != '\n')
	{
		char c = s[i];
		if (c != ' ' && c != '0' && c != '1'
			&& c != 'N' && c != 'S' && c != 'E' && c != 'W')
			return (0);
		if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
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

int	split_config_and_map(char **lines, char ***cfg_out, char ***map_out)
{
	int		i, in_map, c, m;
	char	**cfg, **map;

	cfg = malloc(sizeof(char *) * 100); 
	map = malloc(sizeof(char *) * 100);
	if (!cfg || !map)
		return (0);
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
	*cfg_out = cfg;
	*map_out = map;
	return (1);
}
