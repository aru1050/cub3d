/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:52:34 by athamilc          #+#    #+#             */
/*   Updated: 2025/11/14 18:37:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cub(t_data *d, char **argv)
{
	if (!argv[1])
		die_parse("Error\nMissing .cub file", d);
	d->mlx = mlx_init();
	if (!d->mlx)
		die_parse("Error\nmlx_init failed", d);
	if (!parse_file(argv[1], d))
		die_parse("Error\nparse_file failed", d);
	load_all_textures(d);
	d->win = mlx_new_window(d->mlx, WIDTH, HEIGHT, "cub3d");
	if (!d->win)
		die_parse("Error\nmlx_new_window failed", d);
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	if (!d->img)
		die_parse("Error\nmlx_new_image failed", d);
	d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->line_len, &d->endian);
	if (!d->addr)
		die_parse("Error\nmlx_get_data_addr failed", d);
}

int	shade_color(int color, double f)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) * f;
	g = ((color >> 8) & 0xFF) * f;
	b = (color & 0xFF) * f;
	return (r << 16 | g << 8 | b);
}

void	my_pixel_put(t_data *d, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = d->addr + (y * d->line_len + x * (d->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

void	render_background(t_data *d)
{
	int	x;
	int	y;
	int	ceil_color;
	int	floor_color;

	ceil_color = (d->ceiling.r << 16) | (d->ceiling.g << 8) | d->ceiling.b;
	floor_color = (d->floor.r << 16) | (d->floor.g << 8) | d->floor.b;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				my_pixel_put(d, x, y, ceil_color);
			else
				my_pixel_put(d, x, y, floor_color);
			x++;
		}
		y++;
	}
}
