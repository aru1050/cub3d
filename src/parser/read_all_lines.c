#include "cub3d.h"

/*
** Lis un fichier texte (.cub) ligne par ligne avec get_next_line,
** et renvoie un tableau de chaînes NULL-terminé.
*/

char	**read_all_lines(const char *path)
{
	int		fd;
	char	**lines;
	char	*line;
	int		i;
	int		capacity;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\ncannot open file");
		return (NULL);
	}

	// allocation initiale (tableau de 32 pointeurs)
	capacity = 32;
	lines = malloc(sizeof(char *) * capacity);
	if (!lines)
		return (NULL);

	i = 0;
	while ((line = get_next_line(fd)))
	{
		// si le tableau est plein → on le double
		if (i + 1 >= capacity)
		{
			capacity *= 2;
			lines = realloc(lines, sizeof(char *) * capacity);
			if (!lines)
				return (NULL);
		}
		lines[i++] = line;
	}
	lines[i] = NULL; // marquer la fin du tableau

	close(fd);
	return (lines);
}
