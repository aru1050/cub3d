/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:01:50 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/16 19:59:41 by marvin           ###   ########.fr       */
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
// static void	init_dda(t_ray *ray, t_player *player)
// {
        
// }

// static void	perform_dda(t_ray *r, t_map *map)
// {
// }

// static void	calc_wall(t_ray *r, t_player *p)
// {
// }

// static void	draw_wall(t_data *data, int x, t_ray *r)
// {
// }

// void	render_frames(t_data *data)
// {
// }