/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:58:26 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/31 15:21:52 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(t_map *map, int mx, int my)
{
	char	c;

	if (mx < 0 || my < 0 || mx >= map->width || my >= map->height)
		return (1);
	c = map->grid[my][mx];
	if (c == '1')
		return (1);
	if (c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (1);
	return (0);
}

static void	step_ray(t_ray *r)
{
	if (r->side_x < r->side_y)
	{
		r->side_x += r->delta_x;
		r->map_x += r->step_x;
		r->side = 0;
	}
	else
	{
		r->side_y += r->delta_y;
		r->map_y += r->step_y;
		r->side = 1;
	}
}

static void	compute_distance(t_ray *r, t_player *p)
{
	if (r->side == 0)
		r->dist = (r->map_x - p->x + (1 - r->step_x) / 2.0) / r->dir_x;
	else
		r->dist = (r->map_y - p->y + (1 - r->step_y) / 2.0) / r->dir_y;
	if (r->dist <= 0.0000001)
		r->dist = 0.0000001;
}

static void	dda_until_hit(t_ray *r, t_map *map, t_player *p)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		step_ray(r);
		if (is_wall(map, r->map_x, r->map_y))
			hit = 1;
	}
	compute_distance(r, p);
}

void	rendering_frames(t_data *d)
{
	int		x;
	t_ray	r;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(&r, &d->player, x);
		dda_until_hit(&r, &d->map, &d->player);
		draw_walla(d, x, &r);
		x++;
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
}
