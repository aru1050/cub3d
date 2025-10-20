#include "cub3d.h"

static int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static void	set_player(t_player *pl, int i, int j, char dir)
{
	pl->x = j + 0.5;
	pl->y = i + 0.5;
	pl->dir_x = (dir == 'E') - (dir == 'W');
	pl->dir_y = (dir == 'S') - (dir == 'N');
	pl->plane_x = -pl->dir_y * 0.66;
	pl->plane_y = pl->dir_x * 0.66;
}

void	validate_chars_and_spawn(t_map *map, t_player *pl)
{
	int		i;
	int		j;
	int		spawn;
	char	c;

	i = -1;
	spawn = 0;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			c = map->grid[i][j];
			if (!is_valid_char(c))
				die_parse("Error\nInvalid character in map", NULL);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (++spawn > 1)
					die_parse("Error\nMultiple player spawns", NULL);
				set_player(pl, i, j, c);
				map->grid[i][j] = '0';
			}
		}
	}
	if (spawn == 0)
		die_parse("Error\nNo player found in map", NULL);
}
