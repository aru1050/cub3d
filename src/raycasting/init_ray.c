/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:04:55 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/30 13:00:27 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_ray *ray, t_player *p, int x)
{
	double	camera_x;

	/* 1) Rayon direction (camera_x dans [-1, 1]) */
	camera_x = 2.0 * x / (double)WIDTH - 1.0;
	ray->camera_x = camera_x;
	ray->dir_x = p->dir_x + p->plane_x * camera_x;
	ray->dir_y = p->dir_y + p->plane_y * camera_x;

	/* 2) Case de départ (dans la grille) */
	ray->map_x = (int)p->x;
	ray->map_y = (int)p->y;

	/* 3) Distances delta (protection si dir_x/dir_y = 0) */
	if (ray->dir_x == 0.0)
		ray->delta_x = 1e30; /* ~ infini */
	else
		ray->delta_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0.0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1.0 / ray->dir_y);

	/* 4) Choix des steps et distances initiales jusqu'au premier côté */
	if (ray->dir_x < 0.0)
	{
		ray->step_x = -1;
		ray->side_x = (p->x - (double)ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = ((double)ray->map_x + 1.0 - p->x) * ray->delta_x;
	}
	if (ray->dir_y < 0.0)
	{
		ray->step_y = -1;
		ray->side_y = (p->y - (double)ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = ((double)ray->map_y + 1.0 - p->y) * ray->delta_y;
	}

	/* 5) Par sécurité (sera écrasé par la DDA) */
	ray->side = 0;
	ray->dist = 1.0;
}
