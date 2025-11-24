/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_chars_and_spawn.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:06:26 by athamilc          #+#    #+#             */
/*   Updated: 2025/11/24 01:58:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static void	set_player(t_player *pl, int i, int j, char dir)
{
	pl->x = j + 0.5;
	pl->y = i + 0.5;
	pl->dir_x = (dir == 'E') - (dir == 'W');
	pl->dir_y = (dir == 'S') - (dir == 'N');
	pl->plane_x = -pl->dir_y * 0.66;
	pl->plane_y = pl->dir_x * 0.66;
}

static void	process_cell(t_map *map, t_player *pl, t_data *d, int pos[3])
{
	int		i;
	int		j;
	char	c;

	i = pos[0];
	j = pos[1];
	c = map->grid[i][j];
	if (!is_valid_char(c))
		die_parse("Error\nInvalid character in map", d);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		pos[2]++;
		if (pos[2] > 1)
			die_parse("Error\nMultiple player spawns", d);
		set_player(pl, i, j, c);
		map->grid[i][j] = '0';
	}
}

void	validate_chars_and_spawn(t_map *map, t_player *pl, t_data *d)
{
	int	i;
	int	j;
	int	pos[3];

	i = 0;
	pos[2] = 0;
	while (i < map->height)
	{
		j = 0;
		pos[0] = i;
		while (j < map->width)
		{
			pos[1] = j;
			process_cell(map, pl, d, pos);
			j++;
		}
		i++;
	}
	if (pos[2] == 0)
		die_parse("Error\nNo player found in map", d);
}
