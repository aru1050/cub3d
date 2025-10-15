/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:01:50 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/15 12:28:37 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int init_ray(t_ray *ray)
{
    ray->camera_x;
	ray->dir_x;
	ray->dir_y;
	ray->map_x;
	ray->map_y;
	ray->side_x;
	ray->side_y;
	ray->delta_x;
	ray->delta_y;
	ray->step_x;
	ray->step_y;
	ray->side;
	ray->dist;
	ray->line_height;
	ray->draw_start;
	ray->draw_end;
}

// int cast_rays(t_ray *ray)
// {
    
// }