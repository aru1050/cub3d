/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:04:24 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/20 14:41:36 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		close_window(data);
	if (keycode == W)
		data->player.key_up = 1;
	if (keycode == S)
		data->player.key_down = 1;
	if (keycode == A)
		data->player.key_left = 1;
	if (keycode == D)
		data->player.key_right = 1;
	if (keycode == LEFT_ARROW)
		data->player.left_rotate = 1;
	if (keycode == RIGHT_ARROW)
		data->player.right_rotate = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W)
		data->player.key_up = 0;
	if (keycode == S)
		data->player.key_down = 0;
	if (keycode == A)
		data->player.key_left = 0;
	if (keycode == D)
		data->player.key_right = 0;
	if (keycode == LEFT_ARROW)
		data->player.left_rotate = 0;
	if (keycode == RIGHT_ARROW)
		data->player.right_rotate = 0;
	return (0);
}
int	game_loop(t_data *data)
{
	if (data->player.key_up)
		player_move(W, &data->player);
	if (data->player.key_down)
		player_move(S, &data->player);
	if (data->player.key_left)
		player_move(A, &data->player);
	if (data->player.key_right)
		player_move(D, &data->player);
	if (data->player.left_rotate)
		player_rotate(LEFT_ARROW, &data->player);
	if (data->player.right_rotate)
		player_rotate(RIGHT_ARROW, &data->player);
	render_frames(data);
	return (0);
}

int	close_window(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	printf("Window closed\n");
	exit(0);
	return (0);
}

// int	handle_key(int key, t_data *data)
// {
// 	if (key == ESC)
// 		close_window(data);
// 	player_move(key, &data->player);
//     player_rotate(key, &data->player);
// 	render_frames(data);
// 	return (0);
// }
