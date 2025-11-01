/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:05:58 by athamilc          #+#    #+#             */
/*   Updated: 2025/11/01 18:16:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling_floor(t_data *d, int x, int start, int end)
{
	int	y;
	int	ceil_color;
	int	floor_color;

	ceil_color = (d->ceiling.r << 16) | (d->ceiling.g << 8) | d->ceiling.b;
	floor_color = (d->floor.r << 16) | (d->floor.g << 8) | d->floor.b;
	y = 0;
	while (y < start)
		my_pixel_put(d, x, y++, ceil_color);
	y = end;
	while (y < HEIGHT)
		my_pixel_put(d, x, y++, floor_color);
}

static void	draw_tex_pixel(t_data *d, t_texinfo *info, int x, int y)
{
	char	*px;
	int		color;

	if (info->tex_x < 0)
		info->tex_x = 0;
	if (info->tex_x >= info->tex->width)
		info->tex_x = info->tex->width - 1;
	if (info->tex_y < 0)
		info->tex_y = 0;
	if (info->tex_y >= info->tex->height)
		info->tex_y = info->tex->height - 1;
	px = info->tex->addr
		+ info->tex_y * info->tex->line_len
		+ info->tex_x * (info->tex->bpp / 8);
	color = *(int *)px;
	if (info->side == 1)
		color = shade_color(color, 0.85);
	my_pixel_put(d, x, y, color);
}

static void	draw_wall_texture(t_data *d, t_texture *tex, t_ray *r, int x)
{
	int			y;
	double		step;
	double		texpos;
	t_texinfo	info;

	step = 1.0 * tex->height / r->line_height;
	texpos = (r->draw_start - HEIGHT / 2 + r->line_height / 2) * step;
	draw_ceiling_floor(d, x, r->draw_start, r->draw_end);
	y = r->draw_start;
	while (y < r->draw_end)
	{
		info.tex = tex;
		info.side = r->side;
		info.tex_x = r->tex_x;
		info.tex_y = (int)texpos & (tex->height - 1);
		texpos += step;
		draw_tex_pixel(d, &info, x, y);
		y++;
	}
}

void	draw_wall(t_data *d, int x, t_ray *r)
{
	t_texture	*tex;
	double		wallx;
	int			texx;

	tex = pick_wall_tex(d, r);
	if (r->side == 0)
		wallx = d->player.y + r->dist * r->dir_y;
	else
		wallx = d->player.x + r->dist * r->dir_x;
	wallx -= floor(wallx);
	texx = (int)(wallx * tex->width);
	if (r->side == 0 && r->dir_x > 0)
		texx = tex->width - texx - 1;
	if (r->side == 1 && r->dir_y < 0)
		texx = tex->width - texx - 1;
	r->tex_x = texx;
	draw_wall_texture(d, tex, r, x);
}
