/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:05:58 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/30 13:19:55 by athamilc         ###   ########.fr       */
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

/* ------------------------------ PIXEL WRITER ------------------------------- */

static void	my_pixel_put(t_data *d, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = d->addr + (y * d->line_len + x * (d->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

/* ----------------------------- SIMPLE SHADING ------------------------------ */
/* assombrit légèrement une couleur (0.0–1.0)                                   */

static int	shade_color(int color, double f)
{
	int	r;
	int	g;
	int	b;

	if (f < 0.0)
		f = 0.0;
	if (f > 1.0)
		f = 1.0;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (int)(r * f);
	g = (int)(g * f);
	b = (int)(b * f);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

/* ----------------------------- BACKGROUND F/C ------------------------------ */
/* Optionnel : à appeler AVANT la boucle des colonnes si tu veux peindre
** d'abord le fond ; sinon laisse draw_wall s'en charger colonne par colonne.   */

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

/* ---------------------------- WALL TEXTURING ------------------------------- */

void	draw_walla(t_data *d, int x, t_ray *r)
{
	t_texture	*tex;
	int			line_h;
	int			start;
	int			end;
	double		wallx;
	int			texx;
	int			ceil_color;
	int			floor_color;
	double		step;
	double		texpos;
	int			y;
	int			texy;
	char		*px;
	int			color;

	tex = pick_wall_tex(d, r);
	line_h = (int)(HEIGHT / r->dist);
	start = -line_h / 2 + HEIGHT / 2;
	end = line_h / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	wallx = (r->side == 0)
		? (d->player.y + r->dist * r->dir_y)
		: (d->player.x + r->dist * r->dir_x);
	wallx -= floor(wallx);
	texx = (int)(wallx * (double)tex->width);
	if (r->side == 0 && r->dir_x > 0)
		texx = tex->width - texx - 1;
	if (r->side == 1 && r->dir_y < 0)
		texx = tex->width - texx - 1;
	ceil_color = (d->ceiling.r << 16) | (d->ceiling.g << 8) | d->ceiling.b;
	floor_color = (d->floor.r << 16) | (d->floor.g << 8) | d->floor.b;
	y = 0;
	while (y < start)
	{
		my_pixel_put(d, x, y, ceil_color);
		y++;
	}
	step = 1.0 * tex->height / line_h;
	texpos = (start - HEIGHT / 2 + line_h / 2) * step;
	y = start;
	while (y <= end)
	{
		texy = (int)texpos;
		if (texy < 0)
			texy = 0;
		if (texy >= tex->height)
			texy = tex->height - 1;
		texpos += step;
		px = tex->addr + texy * tex->line_len + texx * (tex->bpp / 8);
		color = *(int *)px;
		if (r->side == 1)
			color = shade_color(color, 0.75);
		my_pixel_put(d, x, y, color);
		y++;
	}
	y = end + 1;
	while (y < HEIGHT)
	{
		my_pixel_put(d, x, y, floor_color);
		y++;
	}
}