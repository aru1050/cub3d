/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:05:58 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/31 14:59:53 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_ceiling_floor(t_data *d, int x, int start, int end)
{
	int	y;
	int	ceil_color;
	int	floor_color;

	ceil_color = (d->ceiling.r << 16) | (d->ceiling.g << 8) | d->ceiling.b;
	floor_color = (d->floor.r << 16) | (d->floor.g << 8) | d->floor.b;
	y = 0;
	while (y < start)
		my_pixel_put(d, x, y++, ceil_color);
	y = end + 1;
	while (y < HEIGHT)
		my_pixel_put(d, x, y++, floor_color);
}

static void	draw_tex_pixel(t_data *d, t_texture *tex, t_ray *r, double *texpos)
{
	int		texy;
	char	*px;
	int		color;

	texy = (int)*texpos;
	if (texy < 0)
		texy = 0;
	if (texy >= tex->height)
		texy = tex->height - 1;
	*texpos += (1.0 * tex->height / r->line_h);
	px = tex->addr + texy * tex->line_len + r->tex_x * (tex->bpp / 8);
	color = *(int *)px;
	if (r->side == 1)
		color = shade_color(color, 0.75);
	my_pixel_put(d, r->x, r->y, color);
}

static void	draw_wall_texture(t_data *d, t_texture *tex, t_ray *r, int x)
{
	int		start;
	int		end;
	double	texpos;

	r->line_h = (int)(HEIGHT / r->dist);
	start = -r->line_h / 2 + HEIGHT / 2;
	end = r->line_h / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	texpos = (start - HEIGHT / 2 + r->line_h / 2)
		* (1.0 * tex->height / r->line_h);
	r->x = x;
	r->y = start;
	while (r->y <= end)
	{
		draw_tex_pixel(d, tex, r, &texpos);
		r->y++;
	}
	draw_ceiling_floor(d, x, start, end);
}

void	draw_walla(t_data *d, int x, t_ray *r)
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
