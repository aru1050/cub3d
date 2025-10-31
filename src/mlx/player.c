/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:06:07 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/31 15:03:35 by athamilc         ###   ########.fr       */
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
	if (map->grid[(int)p->y][(int)new_x] != '1')
		p->x = new_x;
	if (map->grid[(int)new_y][(int)p->x] != '1')
		p->y = new_y;
}

void	player_rotate_left(int key, t_player *player)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = 0.01;
	if (key == LEFT_ARROW)
	{
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(rot_speed)
			- player->dir_y * sin(rot_speed);
		player->dir_y = old_dir_x * sin(rot_speed)
			+ player->dir_y * cos(rot_speed);
		old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(rot_speed)
			- player->plane_y * sin(rot_speed);
		player->plane_y = old_plane_x * sin(rot_speed)
			+ player->plane_y * cos(rot_speed);
	}
}

void	player_rotate_right(int key, t_player *player)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = 0.01;
	if (key == RIGHT_ARROW)
	{
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(-rot_speed)
			- player->dir_y * sin(-rot_speed);
		player->dir_y = old_dir_x * sin(-rot_speed)
			+ player->dir_y * cos(-rot_speed);
		old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(-rot_speed)
			- player->plane_y * sin(-rot_speed);
		player->plane_y = old_plane_x * sin(-rot_speed)
			+ player->plane_y * cos(-rot_speed);
	}
}
