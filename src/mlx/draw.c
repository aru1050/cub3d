/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:05:58 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/07 11:30:46 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_cub(t_data *config, char **argv)
{
	(void)argv;
    config->mlx = mlx_init();
	config->win = mlx_new_window(config->mlx, WIDTH, HEIGHT, "cub3d");
	config->img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
	config->addr = mlx_get_data_addr(config->img, &config->bpp, &config->line_len, &config->endian);
}