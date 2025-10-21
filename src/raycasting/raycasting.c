/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:01:50 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/21 16:01:47 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_ray(t_ray *ray, t_player *player, int x)
{
    ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	if (ray->dir_x == 0)
		ray->delta_x = 1e30; // infini
	else
		ray->delta_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1 / ray->dir_y);
}

static void	init_dda(t_ray *r, t_player *p)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_x = (p->x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->map_x + 1.0 - p->x) * r->delta_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_y = (p->y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->map_y + 1.0 - p->y) * r->delta_y;
	}
}

static void	perform_dda(t_ray *r, t_map *map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
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
		if (map->grid[r->map_y][r->map_x] == '1')
			hit = 1;
	}
}

static void	calc_wall(t_ray *r, t_player *p)
{
	if (r->side == 0)
		r->dist = (r->map_x - p->x + (1 - r->step_x) / 2) / r->dir_x;
	else
		r->dist = (r->map_y - p->y + (1 - r->step_y) / 2) / r->dir_y;
	r->line_height = (int)(HEIGHT / r->dist);
	r->draw_start = -r->line_height / 2 + HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + HEIGHT / 2;
	if (r->draw_end >= HEIGHT)
		r->draw_end = HEIGHT - 1;
}

static void	draw_wall(t_data *data, int x, t_ray *r)
{
	int		y;
	int		color;
	char	*dst;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < r->draw_start)
			color = 0x87CEEB;
		else if (y > r->draw_end)
			color = 0xA0522D;
		else
		{
			if (r->side == 1)
				color = 0xFF0000;
			else
				color = 0x880000;
		}
		dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
		y++;
	}
}

void	render_frames(t_data *data)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(&ray, &data->player, x);
		init_dda(&ray, &data->player);
		perform_dda(&ray, &data->map);
		calc_wall(&ray, &data->player);
		draw_wall(data, x, &ray);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}