/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_closed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcalma <vcalma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:37:38 by vcalma            #+#    #+#             */
/*   Updated: 2025/10/20 15:37:41 by vcalma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

static int	in_bounds(int x, int y, int w, int h)
{
	if (x >= 0 && y >= 0 && x < w && y < h)
		return (1);
	return (0);
}

static void	init_dirs(int *dx, int *dy)
{
	dx[0] = 1;
	dx[1] = -1;
	dx[2] = 0;
	dx[3] = 0;
	dy[0] = 0;
	dy[1] = 0;
	dy[2] = 1;
	dy[3] = -1;
}

static void	mark_outside(char **v, int w, int h, t_point p)
{
	t_point	q[10000];
	int		head;
	int		tail;
	int		dx[4];
	int		dy[4];
	int		i;
	t_point	n;

	init_dirs(dx, dy);
	head = 0;
	tail = 0;
	q[tail++] = p;
	v[p.y][p.x] = '#';
	while (head < tail)
	{
		i = -1;
		while (++i < 4)
		{
			n.x = q[head].x + dx[i];
			n.y = q[head].y + dy[i];
			if (in_bounds(n.x, n.y, w, h) && v[n.y][n.x] == ' ')
			{
				v[n.y][n.x] = '#';
				q[tail++] = n;
			}
		}
		head++;
	}
}

static char	**copy_map(const t_map *map)
{
	char	**v;
	int		y;

	v = malloc(sizeof(char *) * map->height);
	if (!v)
		return (NULL);
	y = 0;
	while (y < map->height)
	{
		v[y] = ft_strdup(map->grid[y]);
		y++;
	}
	return (v);
}

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

static void	check_leaks(char **v, const t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == '0' && (v[y][x] == '#'
					|| v[y][x + 1] == '#' || v[y][x - 1] == '#'
					|| v[y + 1][x] == '#' || v[y - 1][x] == '#'))
				die_parse("Error\nMap not closed", NULL);
			x++;
		}
		free(v[y]);
		y++;
	}
	free(v);
}

void	check_map_closed(const t_map *map)
{
	char	**v;

	v = copy_map(map);
	if (!v)
		die_parse("Error\nMalloc failed (map copy)", NULL);
	fill_borders(v, map);
	check_leaks(v, map);
}
