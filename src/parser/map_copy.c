/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 23:46:34 by marvin            #+#    #+#             */
/*   Updated: 2025/11/24 23:46:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**copy_map(const t_map *map)
{
	char	**v;
	int		y;

	v = malloc(sizeof(char *) * map->height);
	if (!v)
		return (NULL);
	y = 0;
	while (y < map->height)
	{
		v[y] = ft_strdup(map->grid[y]);
		y++;
	}
	return (v);
}

void	free_copy(char **v, int h)
{
	int	y;

	y = 0;
	while (y < h)
	{
		free(v[y]);
		y++;
	}
	free(v);
}
