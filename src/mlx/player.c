/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:06:07 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/09 13:18:22 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player(t_player *player)
{
    player->x = 0.0;
    player->y = 0.0;
    player->dir_x = 0;
    player->dir_y = 0;
    player->plane_x = 0.0;
    player->plane_y = 0.0;
}

// int player_move(int key, t_data *data)
// {
//     if (key == A)
        
//     if (key == W)

//     if (key == D)

//     if (key == X)
// }