/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:01:50 by athamilc          #+#    #+#             */
/*   Updated: 2025/11/01 17:57:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	perform_dda(t_ray *r, t_map *map)
{
	int	hit;

	hit = 0;
	while (!hit)
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
		if (r->map_x < 0 || r->map_y < 0
			|| r->map_y >= map->height || r->map_x >= map->width)
			return (0);
		if (map->grid[r->map_y][r->map_x] == '1')
			hit = 1;
	}
	return (1);
}

static void	calc_wall(t_ray *r, t_player *p)
{
	if (r->side == 0)
		r->dist = (r->map_x - p->x + (1 - r->step_x) / 2) / r->dir_x;
	else
		r->dist = (r->map_y - p->y + (1 - r->step_y) / 2) / r->dir_y;
	if (r->dist <= 0.0001)
		r->dist = 0.0001;
	r->line_height = (int)(HEIGHT / r->dist);
	if (r->line_height > HEIGHT * 4)
		r->line_height = HEIGHT * 4;
	r->draw_start = -r->line_height / 2 + HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + HEIGHT / 2;
	if (r->draw_end >= HEIGHT)
		r->draw_end = HEIGHT - 1;
}

void	render_frames(t_data *data)
{
	int		x;
	t_ray	ray;

	render_background(data);
	x = 0;
	while (x < WIDTH)
	{
		init_ray(&ray, &data->player, x);
		if (perform_dda(&ray, &data->map))
		{
			calc_wall(&ray, &data->player);
			draw_wall(data, x, &ray);
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
