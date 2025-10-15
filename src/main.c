/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:20:15 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/14 13:05:19 by athamilc         ###   ########.fr       */
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
    // parser_mlx(&data);
    init_cub(&data, argv);
    init_player(&data.player);
    
    render_frame(&data);
    mlx_key_hook(data.win, handle_key, &data);
    mlx_hook(data.win, 17, 0, close_window, &data);
    mlx_loop(data.mlx);
    // free_mlx(&data);
    return (0);
}