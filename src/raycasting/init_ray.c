/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:04:55 by athamilc          #+#    #+#             */
/*   Updated: 2025/11/01 17:15:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_ray_delta(t_ray *r)
{
	if (fabs(r->dir_x) < 1e-8)
		r->delta_x = 1e30;
	else
		r->delta_x = fabs(1.0 / r->dir_x);
	if (fabs(r->dir_y) < 1e-8)
		r->delta_y = 1e30;
	else
		r->delta_y = fabs(1.0 / r->dir_y);
}

static void	set_ray_step_x(t_ray *r, t_player *p)
{
	if (r->dir_x < 0.0)
	{
		r->step_x = -1;
		r->side_x = (p->x - (double)r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = ((double)r->map_x + 1.0 - p->x) * r->delta_x;
	}
}

static void	set_ray_step_y(t_ray *r, t_player *p)
{
	if (r->dir_y < 0.0)
	{
		r->step_y = -1;
		r->side_y = (p->y - (double)r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = ((double)r->map_y + 1.0 - p->y) * r->delta_y;
	}
}

void	init_ray(t_ray *r, t_player *p, int x)
{
	if (WIDTH == 0)
		return ;
	r->camera_x = 2.0 * x / (double)WIDTH - 1.0;
	r->dir_x = p->dir_x + p->plane_x * r->camera_x;
	r->dir_y = p->dir_y + p->plane_y * r->camera_x;
	r->map_x = (int)p->x;
	r->map_y = (int)p->y;
	set_ray_delta(r);
	set_ray_step_x(r, p);
	set_ray_step_y(r, p);
	r->side = 0;
	r->dist = 0.0;
}
