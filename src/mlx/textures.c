/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:06:03 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/23 17:52:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(t_data *d, t_texture *tex)
{
	tex->img = mlx_xpm_file_to_image(d->mlx, tex->path,
			&tex->width, &tex->height);
	if (!tex->img)
		die_parse("Error\nFailed to load texture", d);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		die_parse("Error\nmlx_get_data_addr failed", d);
}

void	load_all_textures(t_data *d)
{
	load_texture(d, &d->north);
	load_texture(d, &d->south);
	load_texture(d, &d->west);
	load_texture(d, &d->east);
}