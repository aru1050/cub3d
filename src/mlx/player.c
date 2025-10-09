/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:06:07 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/09 15:06:50 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player(t_player *player)
{
    player->x = 3.5;
    player->y = 3.5;
    player->dir_x = 0;
    player->dir_y = -1;
    player->plane_x = 0.66;
    player->plane_y = 0.0;
}

void player_move(int key, t_player *player)
{
    double move_speed = 0.05;
    
    if (key == A)
    {
        player->x -= player->plane_x * move_speed;
        player->y -= player->plane_y * move_speed;
    }
    if (key == D)
    {
        player->x += player->plane_x * move_speed;
        player->y += player->plane_y * move_speed;
    }    
    if (key == W)
    {
        player->x += player->dir_x * move_speed;
        player->y += player->dir_y * move_speed;
    }
    if (key == S)
    {
        player->x -= player->dir_x * move_speed;
        player->y -= player->dir_y * move_speed;
    }
}

void player_rotate(int key, t_player *player)
{
    double rot_speed = 0.03;
    double old_dir_x;
    double old_plane_x;

    if (key == RIGHT_ARROW)
    {
        old_dir_x = player->dir_x;
        player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y * sin(rot_speed);
        player->dir_y = old_dir_x * sin(rot_speed) + player->dir_y * cos(rot_speed);

        old_plane_x = player->plane_x;
        player->plane_x = player->plane_x * cos(rot_speed) - player->plane_y * sin(rot_speed);
        player->plane_y = old_plane_x * sin(rot_speed) + player->plane_y * cos(rot_speed);
    }
    if (key == LEFT_ARROW)
    {
        old_dir_x = player->dir_x;
        player->dir_x = player->dir_x * cos(-rot_speed) - player->dir_y * sin(-rot_speed);
        player->dir_y = old_dir_x * sin(-rot_speed) + player->dir_y * cos(-rot_speed);

        old_plane_x = player->plane_x;
        player->plane_x = player->plane_x * cos(-rot_speed) - player->plane_y * sin(-rot_speed);
        player->plane_y = old_plane_x * sin(-rot_speed) + player->plane_y * cos(-rot_speed);
    }
}
