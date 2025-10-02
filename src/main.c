/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:20:15 by athamilc          #+#    #+#             */
/*   Updated: 2025/09/30 11:38:04 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
    t_data config;
// ne pas oublier fonction (.cub)
    ft_memset(&config, 0, sizeof(config));
    if (argc != 2)
    {
        printf("Invalid number of arguments.\n");
        return (1);
    }
    parser_mlx(&config);
    init_mlx(&config);
    draw_mlx(&config);
    free_mlx(&config);
    return (0);
}