/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:12:07 by athamilc          #+#    #+#             */
/*   Updated: 2025/11/03 12:13:36 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
