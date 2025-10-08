/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:20:15 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/08 15:23:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
    t_data data;
// ne pas oublier fonction (.cub)
    ft_memset(&data, 0, sizeof(data));
    if (argc != 2)
    {
        printf("Invalid number of arguments.\n");
        return (1);
    }
    // parser_mlx(&config);
    init_cub(&data, argv);
    render_frame(&data);
    mlx_hook(data.win, 2, 1L << 0, handle_key, &data);
    mlx_hook(data.win, 17, 0, close_window, &data);
    mlx_loop(data.mlx);
    // draw_mlx(&data);
    // free_mlx(&data);
    return (0);
}