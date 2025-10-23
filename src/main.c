/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:20:15 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/23 17:19:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		die_parse("Error\nUsage: ./cub3D <map.cub>", NULL);
	ft_memset(&data, 0, sizeof(t_data));
	parse_file(argv[1], &data);
	// load_all_textures(&data);
	init_cub(&data, argv);
	init_player(&data.player);
	render_frames(&data);
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}