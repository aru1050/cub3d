/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_all_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcalma <vcalma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:38:16 by vcalma            #+#    #+#             */
/*   Updated: 2025/10/20 15:38:17 by vcalma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	capacity = 32;
	lines = malloc(sizeof(char *) * capacity);
	if (!lines)
		return (NULL);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		if (i + 1 >= capacity)
		{
			capacity *= 2;
			lines = realloc(lines, sizeof(char *) * capacity);
			if (!lines)
				return (NULL);
		}
		lines[i++] = line;
	}
	lines[i] = NULL; 
	close(fd);
	return (lines);
}
