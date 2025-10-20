#include "cub3d.h"

static int	get_width(char **raw)
{
	int	i;
	int	len;
	int	width;

	i = 0;
	width = 0;
	while (raw[i])
	{
		len = ft_strlen(raw[i]);
		if (len > width)
			width = len;
		i++;
	}
	return (width);
}

void	normalize_map(char **raw, t_map *map)
{
	int		i;
	int		j;
	int		len;

	map->height = 0;
	map->width = get_width(raw);
	while (raw[map->height])
		map->height++;
	map->grid = malloc(sizeof(char *) * map->height);
	if (!map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = malloc(map->width + 1);
		ft_memset(map->grid[i], ' ', map->width);
		len = ft_strlen(raw[i]);
		j = 0;
		while (j < len)
		{
			map->grid[i][j] = raw[i][j];
			j++;
		}
		map->grid[i][map->width] = '\0';
		i++;
	}
}
