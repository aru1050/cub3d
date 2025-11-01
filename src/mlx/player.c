/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:06:07 by athamilc          #+#    #+#             */
/*   Updated: 2025/11/01 17:50:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player)
{
	player->x = 2.5;
	player->y = 2.5;
	player->dir_x = -1.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.66;
}

static void	move_direction(int keycode, t_player *p, double *nx, double *ny)
{
	if (keycode == W)
	{
		*nx += p->dir_x * MOVE_SPEED;
		*ny += p->dir_y * MOVE_SPEED;
	}
	else if (keycode == S)
	{
		*nx -= p->dir_x * MOVE_SPEED;
		*ny -= p->dir_y * MOVE_SPEED;
	}
	else if (keycode == A)
	{
		*nx -= p->plane_x * MOVE_SPEED;
		*ny -= p->plane_y * MOVE_SPEED;
	}
	else if (keycode == D)
	{
		*nx += p->plane_x * MOVE_SPEED;
		*ny += p->plane_y * MOVE_SPEED;
	}
}

void	player_move(int keycode, t_player *p, t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = p->x;
	new_y = p->y;
	move_direction(keycode, p, &new_x, &new_y);
	if ((int)new_x >= 0 && (int)new_x < map->width
		&& map->grid[(int)p->y][(int)new_x] != '1')
		p->x = new_x;
	if ((int)new_y >= 0 && (int)new_y < map->height
		&& map->grid[(int)new_y][(int)p->x] != '1')
		p->y = new_y;
}

void	player_rotate(t_player *p, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
	p->dir_y = old_dir_x * sin(rot) + p->dir_y * cos(rot);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
	p->plane_y = old_plane_x * sin(rot) + p->plane_y * cos(rot);
}
