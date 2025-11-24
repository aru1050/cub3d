/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_closed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:05:55 by athamilc          #+#    #+#             */
/*   Updated: 2025/11/24 23:48:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_borders(char **v, const t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if ((y == 0 || x == 0 || y == map->height - 1
					|| x == map->width - 1) && v[y][x] == ' ')
				mark_outside(v, map->width, map->height,
					(t_point){x, y});
			x++;
		}
		y++;
	}
}

static void	check_leaks(char **v, const t_map *map, t_data *d)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == '0' && (y == 0 || x == 0
				|| y == map->height - 1 || x == map->width - 1
				|| v[y][x] == '#' || v[y][x + 1] == '#'
				|| v[y][x - 1] == '#' || v[y + 1][x] == '#'
				|| v[y - 1][x] == '#'))
			{
				free_copy(v, map->height);
				die_parse("Error\nMap not closed", d);
			}
			x++;
		}
		y++;
	}
}

void	check_map_closed(const t_map *map, t_data *d)
{
	char	**v;

	v = copy_map(map);
	if (!v)
		die_parse("Error\nMalloc failed (map copy)", d);
	fill_borders(v, map);
	check_leaks(v, map, d);
	free_copy(v, map->height);
}
