/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athamilc <athamilc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:06:11 by athamilc          #+#    #+#             */
/*   Updated: 2025/10/21 12:06:12 by athamilc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_rgb_values(char *str, t_color *color)
{
	char	**split;
	int		r, g, b;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		return (0);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_strarray(split);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	color->r = r;
	color->g = g;
	color->b = b;
	return (1);
}

void	parse_colors(char **cfg, t_data *d)
{
	int	i;
	int	has_floor;
	int	has_ceiling;

	i = 0;
	has_floor = 0;
	has_ceiling = 0;
	while (cfg[i])
	{
		if (cfg[i][0] == 'F' && ft_isspace(cfg[i][1]))
		{
			if (has_floor++)
			{
				printf("Error\nDuplicate floor color (F)\n");
				exit(1);
			}
			if (!parse_rgb_values(cfg[i] + 2, &d->floor))
			{
				printf("Error\nInvalid RGB for F\n");
				exit(1);
			}
		}
		else if (cfg[i][0] == 'C' && ft_isspace(cfg[i][1]))
		{
			if (has_ceiling++)
			{
				printf("Error\nDuplicate ceiling color (C)\n");
				exit(1);
			}
			if (!parse_rgb_values(cfg[i] + 2, &d->ceiling))
			{
				printf("Error\nInvalid RGB for C\n");
				exit(1);
			}
		}
		i++;
	}
	if (!has_floor || !has_ceiling)
	{
		printf("Error\nMissing F and/or C\n");
		exit(1);
	}
}
