/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:04:24 by athamilc          #+#    #+#             */
/*   Updated: 2025/11/03 12:22:53 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		close_window(data);
	else if (keycode == W)
		data->player.key_up = 1;
	else if (keycode == S)
		data->player.key_down = 1;
	else if (keycode == A)
		data->player.key_left = 1;
	else if (keycode == D)
		data->player.key_right = 1;
	else if (keycode == LEFT_ARROW)
		data->player.left_rotate = 1;
	else if (keycode == RIGHT_ARROW)
		data->player.right_rotate = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W)
		data->player.key_up = 0;
	else if (keycode == S)
		data->player.key_down = 0;
	else if (keycode == A)
		data->player.key_left = 0;
	else if (keycode == D)
		data->player.key_right = 0;
	else if (keycode == LEFT_ARROW)
		data->player.left_rotate = 0;
	else if (keycode == RIGHT_ARROW)
		data->player.right_rotate = 0;
	return (0);
}

int	game_loop(t_data *data)
{
	if (data->player.key_up)
		player_move(W, &data->player, &data->map);
	if (data->player.key_down)
		player_move(S, &data->player, &data->map);
	if (data->player.key_left)
		player_move(A, &data->player, &data->map);
	if (data->player.key_right)
		player_move(D, &data->player, &data->map);
	if (data->player.left_rotate)
		player_rotate(&data->player, -0.03);
	if (data->player.right_rotate)
		player_rotate(&data->player, 0.03);
	render_frames(data);
	return (0);
}
