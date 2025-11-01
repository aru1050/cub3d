/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:04:24 by athamilc          #+#    #+#             */
/*   Updated: 2025/11/01 18:29:52 by marvin           ###   ########.fr       */
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
		player_rotate(&data->player, -0.05);
	if (data->player.right_rotate)
		player_rotate(&data->player, 0.05);
	render_frames(data);
	return (0);
}

static void	free_map(t_map *map)
{
	int	y;

	if (!map || !map->grid)
		return ;
	y = 0;
	while (y < map->height)
	{
		free(map->grid[y]);
		y++;
	}
	free(map->grid);
	map->grid = NULL;
}

static void	free_texture_paths(t_data *d)
{
	if (d->north.path)
		free(d->north.path);
	if (d->south.path)
		free(d->south.path);
	if (d->west.path)
		free(d->west.path);
	if (d->east.path)
		free(d->east.path);
	d->north.path = NULL;
	d->south.path = NULL;
	d->west.path = NULL;
	d->east.path = NULL;
}

int	close_window(t_data *data)
{
	if (!data || data->is_closed)
		return (0);
	data->is_closed = 1;
	destroy_all_textures(data);
	free_texture_paths(data);
	free_map(&data->map);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
	return (0);
}